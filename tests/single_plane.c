/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:27:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/13 10:25:58 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_plane(t_plane *pl);
static void	cast_rays_at_plane(t_plane const *pl, t_phong_helper *p);
static void	single_plane_test(void);

/**
 * @returns The program's primary data struct
 */
t_data	*dat(void)
{
	static t_data	data;

	return (&data);
}

int	main(void)
{
	dat()->elems.camera = ft_calloc(1, sizeof(t_camera));
	dat()->elems.camera->fov = 60;
	dat()->elems.lights = ft_calloc(1, sizeof(t_light));
	dat()->elems.ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	if (data_init_successful() == false)
		return (dat()->error);
	setup_pixel_grid(dat()->img->width, dat()->img->height);
	single_plane_test();
	mlx_loop(dat()->mlx);
	mlx_terminate(dat()->mlx);
	free_data();
	return (0);
}

static void	single_plane_test(void)
{
	t_plane	pl;

	pl.pos = point(0, 10, 0);
	pl.orientation = vector(0, -1, -0.1);
	pl.transform = translation_m4x4(pl.pos);
	pl.inverse = inverse_m4x4(pl.transform);
	pl.material = default_material();
	pl.material.color = point(0, 0, 1);
	dat()->elems.lights->pos = point(-50, 0, 0);
	dat()->elems.lights->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	dat()->elems.lights->brightness = 1;
	dat()->elems.lights->transform = translation_m4x4(dat()->elems.lights->pos);
	dat()->elems.lights->inverse = inverse_m4x4(dat()->elems.lights->transform);
	dat()->elems.ambient_light->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	dat()->elems.ambient_light->brightness = 0.0;
	light_single_plane(&pl);
}

static void	light_single_plane(t_plane *pl)
{
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = pl->material;
	cast_rays_at_plane(pl, &p);
}

static void	cast_rays_at_plane(t_plane const *pl, t_phong_helper *p)
{
	t_ray_x_obj	rxo;
	t_ray		ray;
	t_flt_color	color;
	size_t		i;

	i = -1;
	while (++i < dat()->pixel_count)
	{
		p->diffuse = (t_vec4){};
		p->specular = (t_vec4){};
		ray = ray_for_pixel(i);
		rxo = ray_x_plane(ray, pl);
		if (rxo.t <= 0)
			continue ;
		p->ray = &ray;
		p->pos = ray_position(ray, rxo.t);
		p->to_cam = opposite_vec(ray.dir);
		p->normal = pl->orientation;
		p->obj_hit = ray.closest_hit.obj;
		color = let_there_be_light(p);
		set_pixel_color(i, color_flt_to_8bit(color));
	}
}
