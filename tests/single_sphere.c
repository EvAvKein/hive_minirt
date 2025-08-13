/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:58:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/13 10:21:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	single_sphere_test(void);
static void	light_single_sphere(t_sphere const *sp);
static void	cast_rays_at_sphere(t_sphere const *sp, t_phong_helper *p);

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
	single_sphere_test();
	mlx_loop(dat()->mlx);
	mlx_terminate(dat()->mlx);
	free_data();
	return (0);
}

static void	single_sphere_test(void)
{
	t_sphere	sp;

	sp.pos = point(0, 0, 20);
	sp.radius = 2.5;
	sp.transform = scaling_m4x4(vector(1, 0.5, 1));
	sp.transform = mult_m4x4(translation_m4x4(sp.pos), sp.transform);
	sp.inverse = inverse_m4x4(sp.transform);
	sp.material = default_material();
	sp.material.color = point(1, 0, 1);
	dat()->elems.lights->pos = point(0, 7, 20);
	dat()->elems.lights->color = (t_flt_color){.r = 1, .g = 1, .b = 1};
	dat()->elems.lights->brightness = 1;
	dat()->elems.lights->transform = translation_m4x4(dat()->elems.lights->pos);
	dat()->elems.lights->inverse = inverse_m4x4(dat()->elems.lights->transform);
	light_single_sphere(&sp);
}

static void	light_single_sphere(t_sphere const *sp)
{
	t_phong_helper	p;

	p = (t_phong_helper){0};
	p.mat = sp->material;
	cast_rays_at_sphere(sp, &p);
}

static void	cast_rays_at_sphere(t_sphere const *sp, t_phong_helper *p)
{
	t_ray_x_obj		rxo;
	t_ray			ray;
	t_flt_color		color;
	size_t			i;

	i = -1;
	while (++i < dat()->pixel_count)
	{
		p->diffuse = (t_vec4){};
		p->specular = (t_vec4){};
		ray = ray_for_pixel(i);
		rxo = hit(ray_x_sphere(ray, sp));
		if (rxo.t <= 0)
			continue ;
		p->ray = &ray;
		p->pos = ray_position(ray, rxo.t);
		p->to_cam = opposite_vec(ray.dir);
		p->normal = sphere_normal_at(*sp, p->pos);
		p->obj_hit = ray.closest_hit.obj;
		color = let_there_be_light(p);
		set_pixel_color(i, color_flt_to_8bit(color));
	}
}
