/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:27:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/10 11:42:52 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_plane(t_plane *pl, t_light *light);
static void	cast_rays_at_plane(t_plane const *pl, t_phong_helper *p);

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
	light.color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	light.brightness = 1;
	light.transform = identity_m4x4();
	light.inverse = identity_m4x4();
	light_single_plane(&pl, &light);
}

static void	light_single_plane(t_plane *pl, t_light *light)
{
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = pl->material;
	p.light = light;
	cast_rays_at_plane(pl, &p);
}

static void	cast_rays_at_plane(t_plane const *pl, t_phong_helper *p)
{
	t_ray_x_obj	rxo;
	t_ray		ray;
	t_flt_color	color;
	size_t		i;

	i = -1;
	while (++i < g_data.pixel_count)
	{
		ray = ray_for_pixel(i);
		rxo = ray_x_plane(ray, pl);
		if (rxo.t <= 0)
			continue ;
		p->pos = ray_position(ray, rxo.t);
		p->normal = pl->orientation;
		p->to_cam = opposite_vec(ray.dir);
		color = let_there_be_light(p);
		set_pixel_color(i, color_flt_to_8bit(color));
	}
}
