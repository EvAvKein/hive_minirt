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

t_data	g_data;

int	main(void)
{
	ft_bzero(&g_data, sizeof(t_data));
	g_data.elems.camera = ft_calloc(1, sizeof(t_camera));
	g_data.elems.camera->fov = 60;
	g_data.elems.lights = ft_calloc(1, sizeof(t_light));
	g_data.elems.ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	if (data_init_successful() == false)
		return (g_data.error);
	setup_pixel_grid(g_data.img->width, g_data.img->height);
	single_cylinder_test();
	mlx_loop(g_data.mlx);
	mlx_terminate(g_data.mlx);
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
	g_data.elems.lights->pos = point(-50, 0, 0);
	g_data.elems.lights->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	g_data.elems.lights->brightness = 1;
	g_data.elems.lights->transform = translation_m4x4(g_data.elems.lights->pos);
	g_data.elems.lights->inverse = inverse_m4x4(g_data.elems.lights->transform);
	g_data.elems.ambient_light->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	g_data.elems.ambient_light->brightness = 0.0;
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
	while (++i < g_data.pixel_count) {
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
