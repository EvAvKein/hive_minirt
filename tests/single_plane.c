/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:27:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/15 15:52:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_plane(t_plane *pl, t_light *light);
static void	cast_rays_at_plane(t_data *const data, t_plane const *pl,
				t_phong_helper *p);

void	single_plane_test(void)
{
	t_plane	pl;
	t_light	light;

	pl.pos = point(0, 10, 0);
	pl.orientation = vector(0, -1, -0.1);
	pl.transform = translation_m4x4(pl.pos);
	pl.inverse = inverse_m4x4(pl.transform);
	pl.material = default_material();
	pl.material.color = point(0, 0, 1);
	light.pos = point(20, 80, -10);
	light.color = (t_color){.bit = (t_8bit_color){.rgba = 0xffffffff}};
	light.color.flt = color_8bit_to_float(light.color.bit);
	light.brightness = 1;
	light.transform = identity_m4x4();
	light.inverse = identity_m4x4();
	light_single_plane(&pl, &light);
}

static void	light_single_plane(t_plane *pl, t_light *light)
{
	t_data *const	data = get_data();
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = pl->material;
	p.light = light;
	cast_rays_at_plane(data, pl, &p);
}

static void	cast_rays_at_plane(t_data *const data, t_plane const *pl,
					t_phong_helper *p)
{
	t_ray_x_obj	rxo;
	t_ray		ray;
	t_color		color;
	size_t		i;

	i = -1;
	while (++i < data->pixel_count)
	{
		ray = data->pixel_rays[i];
		rxo = ray_x_plane(ray, pl);
		if (rxo.t <= 0)
			continue ;
		p->pos = ray_position(ray, rxo.t);
		p->normal = pl->orientation;
		p->to_cam = opposite_vec(ray.dir);
		color = let_there_be_light(p);
		set_pixel_color(i, color);
	}
}
