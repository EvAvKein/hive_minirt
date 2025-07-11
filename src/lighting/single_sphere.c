/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:58:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/11 11:01:10 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_sphere(t_sphere *sp, t_light const *light);
static void	cast_rays_at_sphere(t_data const *data, t_sphere *sp,
				t_phong_helper *p);

void	single_sphere_test(void)
{
	t_data *const	data = get_data();
	t_sphere		sp;
	t_light			light;

	data->elems.camera->orientation = vector(0, 0, 1);
	sp.pos = position(0, 0, 30);
	sp.radius = 3;
	sp.transform = identity_m4x4();
	sp.inverse = inverse_m4x4(sp.transform);
	sp.material = default_material();
	sp.material.color = (t_vec4){
		.axis.x = 1,
		.axis.y = 0,
		.axis.z = 1,
		.axis.w = 1,
	};
	sp.material.ambient = .2;
	light.pos = position(20, 80, -10);
	light.color = (t_color){.bit = (t_8bit_color){.rgba = 0xffffffff}};
	light.brightness = 1;
	light.transform = identity_m4x4();
	light.color.flt = color_8bit_to_float(light.color.bit);
	light_single_sphere(&sp, &light);
}

static void	light_single_sphere(t_sphere *sp, t_light const *light)
{
	t_data *const	data = get_data();
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = &sp->material;
	p.light = light;
	cast_rays_at_sphere(data, sp, &p);
}

static void	cast_rays_at_sphere(t_data const *data, t_sphere *sp,
				t_phong_helper *p)
{
	t_ray_x_objs	rxos;
	t_ray_x_obj		rxo;
	t_ray			ray;
	t_color			color;
	size_t			i;

	i = -1;
	while (++i < data->pixel_count)
	{
		ray = data->pixel_rays[i];
		p->to_cam = scaled_vec(ray.dir, -1);
		rxos = ray_x_sphere(ray, sp);
		rxo = hit(rxos);
		if (rxo.t <= 0)
			continue ;
		p->pos = scaled_vec(ray.dir, rxo.t);
		p->normal = sphere_normal_at(*sp, ray, rxo);
		color = let_there_be_light(p);
		data->img->pixels[i * 4 + 0] = color.bit.channel.r;
		data->img->pixels[i * 4 + 1] = color.bit.channel.g;
		data->img->pixels[i * 4 + 2] = color.bit.channel.b;
		data->img->pixels[i * 4 + 3] = 0xff;
	}
}
