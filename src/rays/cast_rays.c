/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:44:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/17 12:32:00 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Struct containing the smallest non-negative t-valued intersection
 *			in rxos (ray-object intersections), 0 struct when both t-values
 *			are negative
 */
t_ray_x_obj	hit(t_ray_x_objs rxos)
{
	if (rxos._[0].t < 0 && rxos._[1].t < 0)
		return ((t_ray_x_obj){0});
	if (rxos._[0].t < 0)
		return (rxos._[1]);
	if (rxos._[1].t > 0
		&& rxos._[0].t > rxos._[1].t)
		return (rxos._[1]);
	return (rxos._[0]);
}

/**
 * @returns The closest intersection in the provided intersections array
 */
static t_ray_x_obj	*closest_rxo(t_ray_x_obj_array *array)
{
	t_ray_x_obj	*rxo;
	size_t		i;
	t_flt		t;

	rxo = NULL;
	i = -1;
	while (++i < array->idx)
	{
		t = array->_[i].t;
		if (t > EPSILON && (!rxo || t < rxo->t))
			rxo = &array->_[i];
	}
	return (rxo);
}

/**
 * @returns The color at the provided intersection
 */
static t_color	color_at_obj_hit(t_ray_x_obj *rxo, t_phong_helper *phong)
{
	if (rxo->obj_type == SPHERE)
	{
		phong->normal = sphere_normal_at(*(t_sphere *)rxo->obj, phong->pos);
		phong->light = get_data()->elems.lights;
		phong->mat = &((t_sphere *)rxo->obj)->material;
		return (let_there_be_light(phong));
	}
	return ((t_color){0});
}

/**
 * Sets the image's pixel values by raytracing the scene
 */
void	cast_rays(void)
{
	t_data *const	data = get_data();
	size_t			i;
	t_ray			ray;
	t_ray_x_obj		*rxo;
	t_phong_helper	phong;

	i = -1;
	ray = (t_ray){0};
	phong = (t_phong_helper){0};
	while (++i < data->pixel_count)
	{
		free(ray.intersections._);
		xinit_ray_intersections(&ray);
		ray = data->pixel_rays[i];
		ray = transformed_ray(ray, data->elems.camera->transform);
		phong.to_cam = scaled_vec(ray.dir, -1);
		cast_ray_at_objs(&ray, &get_data()->elems, NULL);
		rxo = closest_rxo(&ray.intersections);
		if (!rxo)
			continue ;
		phong.obj_hit = rxo->obj;
		phong.pos = vec_sum(ray.orig, scaled_vec(ray.dir, rxo->t));
		set_pixel_color(i, color_at_obj_hit(rxo, &phong));
		rxo = NULL;
	}
}
