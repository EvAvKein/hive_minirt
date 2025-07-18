/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:13:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/17 11:32:54 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_cylinder(t_cylinder const *cyl, t_light const *light);
static void	cast_rays_at_cylinder(t_data const *data, t_cylinder const *cyl,
				t_phong_helper *p);

void	single_cylinder_test(void)
{
	t_cylinder	cyl;
	t_light		light;

	cyl.pos = position(0, 0, 20);
	cyl.diam = 10;
	cyl.height = 10;
	cyl.orientation = vector(0, 0.9, 1);
	cyl.material = default_material();
	cyl.material.shininess = 200;
	cyl.material.color = position(1, 0, 1);
	init_cylinder_transform(&cyl);
	light.pos = position(0, 10, 20);
	light.color = (t_color){.bit = (t_8bit_color){.rgba = 0xffffffff}};
	light.color.flt = color_8bit_to_float(light.color.bit);
	light.brightness = 1;
	light.transform = translation_m4x4(light.pos);
	light.inverse = inverse_m4x4(light.transform);
	light_single_cylinder(&cyl, &light);
}

static void	light_single_cylinder(t_cylinder const *cyl, t_light const *light)
{
	t_data *const	data = get_data();
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = &cyl->material;
	p.light = light;
	cast_rays_at_cylinder(data, cyl, &p);
}

static void	cast_rays_at_cylinder(t_data const *data, t_cylinder const *cyl,
				t_phong_helper *p)
{
	t_ray			ray;
	t_ray_x_obj		rxo;
	t_color			color;
	size_t			i;

	i = -1;
	while (++i < data->pixel_count)
	{
		ray = data->pixel_rays[i];
		ray = transformed_ray(ray, data->elems.camera->transform);
		rxo = ray_hit_cylinder(ray, cyl);
		if (rxo.t <= 0)
			continue ;
		p->pos = ray_position(ray, rxo.t);
		p->normal = cylinder_normal_at(*cyl, p->pos);
		p->to_cam = opposite_vec(ray.dir);
		if (dot(p->normal, p->to_cam) < 0)
			p->normal = opposite_vec(p->normal);
		color = let_there_be_light(p);
		set_pixel_color(i, color);
	}
}
