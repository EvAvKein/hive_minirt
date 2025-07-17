/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:58:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/15 15:23:08 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_sphere(t_sphere const *sp, t_light const *light);
static void	cast_rays_at_sphere(t_data const *data, t_sphere const *sp,
				t_phong_helper *p);

void	single_sphere_test(void)
{
	t_sphere	sp;
	t_light		light;

	sp.pos = position(0, 0, 20);
	sp.radius = 2.5;
	sp.transform = scaling_m4x4(vector(1, 0.5, 1));
	sp.transform = mult_m4x4(translation_m4x4(sp.pos), sp.transform);
	sp.inverse = inverse_m4x4(sp.transform);
	sp.material = default_material();
	sp.material.color = position(1, 0, 1);
	light.pos = position(0, 7, 20);
	light.color = (t_color){.bit = (t_8bit_color){.rgba = 0xffffffff}};
	light.color.flt = color_8bit_to_float(light.color.bit);
	light.brightness = 1;
	light.transform = translation_m4x4(light.pos);
	light.inverse = inverse_m4x4(light.transform);
	light_single_sphere(&sp, &light);
}

static void	light_single_sphere(t_sphere const *sp, t_light const *light)
{
	t_data *const	data = get_data();
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = &sp->material;
	p.light = light;
	cast_rays_at_sphere(data, sp, &p);
}

static void	cast_rays_at_sphere(t_data const *data, t_sphere const *sp,
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
		ray = transformed_ray(ray, data->elems.camera->transform);
		rxos = ray_x_sphere(ray, sp);
		rxo = hit(rxos);
		if (rxo.t <= 0)
			continue ;
		p->pos = ray_position(ray, rxo.t);
		p->normal = sphere_normal_at(*sp, p->pos);
		p->to_cam = opposite_vec(ray.dir);
		color = let_there_be_light(p);
		set_pixel_color(i, color);
	}
}
