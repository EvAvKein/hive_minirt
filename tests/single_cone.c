/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:23:02 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/11 17:59:05 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_single_cone(t_cone const *cn);
static void	cast_rays_at_cone(t_cone const *cn, t_phong_helper *p);
static void	single_cone_test(void);
static void	init_cone_transform(t_cone *cn);

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
	single_cone_test();
	mlx_loop(g_data.mlx);
	mlx_terminate(g_data.mlx);
	free_data();
	return (0);
}

static void	single_cone_test(void)
{
	t_cone	cn;

	cn.pos = point(0, 0, 20);
	cn.diam = 3;
	cn.height = 6;
	cn.orientation = vector(1, 1, 1);
	cn.material = default_material();
	cn.material.color = point(1, 0, 1);
	init_cone_transform(&cn);
	g_data.elems.lights->pos = point(-50, 0, 0);
	g_data.elems.lights->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	g_data.elems.lights->brightness = 1;
	g_data.elems.lights->transform = translation_m4x4(g_data.elems.lights->pos);
	g_data.elems.lights->inverse = inverse_m4x4(g_data.elems.lights->transform);
	g_data.elems.ambient_light->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	g_data.elems.ambient_light->brightness = 0.0;
	light_single_cone(&cn);
}

static void	init_cone_transform(t_cone *cn)
{
	t_vec2	angles;
	t_plane	pl;

	if (vecs_are_equal(cn->orientation, (t_vec4){}))
		cn->orientation = (t_vec4){.y = 1};
	cn->orientation = unit_vec(cn->orientation);
	pl.orientation = cn->orientation;
	angles = plane_pitch_and_yaw(pl);
	cn->transform = x_rotation_m4x4(angles.x);
	cn->transform = mult_m4x4(y_rotation_m4x4(angles.y), cn->transform);
	cn->transform = mult_m4x4(translation_m4x4(cn->pos), cn->transform);
	cn->inverse = inverse_m4x4(cn->transform);
}

static void	light_single_cone(t_cone const *cn)
{
	t_phong_helper	p;

	p = (t_phong_helper){};
	p.mat = cn->material;
	cast_rays_at_cone(cn, &p);
}

static void	cast_rays_at_cone(t_cone const *cn, t_phong_helper *p)
{
	t_ray		ray;
	t_ray_x_obj	rxo;
	t_flt_color	color;
	size_t		i;

	i = -1;
	while (++i < g_data.pixel_count)
	{
		p->diffuse = (t_vec4){};
		p->specular = (t_vec4){};
		ray = ray_for_pixel(i);
		rxo = hit(ray_x_cone_shell(ray, cn));
		if (rxo.t < EPSILON)
			continue ;
		p->ray = &ray;
		p->pos = ray_position(ray, rxo.t);
		p->to_cam = opposite_vec(ray.dir);
		p->normal = cone_normal_at(*cn, p->pos);
		p->obj_hit = ray.closest_hit.obj;
		color = let_there_be_light(p);
		set_pixel_color(i, color_flt_to_8bit(color));
	}
}
