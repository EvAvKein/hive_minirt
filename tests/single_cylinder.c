/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:13:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/11 17:55:48 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_cylinder(t_cylinder const *cyl);
static void	cast_rays_at_cylinder(t_cylinder const *cyl, t_phong_helper *p);
static void	single_cylinder_test(void);

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
	single_cylinder_test();
	mlx_loop(dat()->mlx);
	mlx_terminate(dat()->mlx);
	free_data();
	return (0);
}

static void single_cylinder_test(void)
{
	t_cylinder	cyl;

	cyl.pos = point(0, 0, 20);
	cyl.diam = 1;
	cyl.height = 1;
	cyl.orientation = vector(0, 1, 0);
	cyl.material = default_material();
	cyl.material.color = point(1, 0, 1);
	init_cylinder_transform(&cyl);
	dat()->elems.lights->pos = point(-50, 0, 0);
	dat()->elems.lights->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	dat()->elems.lights->brightness = 1;
	dat()->elems.lights->transform = translation_m4x4(dat()->elems.lights->pos);
	dat()->elems.lights->inverse = inverse_m4x4(dat()->elems.lights->transform);
	dat()->elems.ambient_light->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	dat()->elems.ambient_light->brightness = 0.0;
	light_single_cylinder(&cyl);
}

static void light_single_cylinder(t_cylinder const *cyl)
{
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = cyl->material;
	cast_rays_at_cylinder(cyl, &p);
}

static void cast_rays_at_cylinder(t_cylinder const *cyl, t_phong_helper *p)
{
	t_ray		ray;
	t_ray_x_obj	rxo;
	t_flt_color	color;
	size_t		i;

	i = -1;
	while (++i < dat()->pixel_count) {
		p->diffuse = (t_vec4){};
		p->specular = (t_vec4){};
		ray = ray_for_pixel(i);
		rxo = ray_hit_cylinder(ray, cyl);
		if (rxo.t < EPSILON)
			continue ;
		p->ray = &ray;
		p->pos = ray_position(ray, rxo.t);
		p->to_cam = opposite_vec(ray.dir);
		p->normal = cylinder_normal_at(*cyl, p->pos);
		p->obj_hit = ray.closest_hit.obj;
		color = let_there_be_light(p);
		set_pixel_color(i, color_flt_to_8bit(color));
	}
}
