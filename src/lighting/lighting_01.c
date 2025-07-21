/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:50:49 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/17 12:37:26 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_diffuse_and_specular(t_phong_helper *p);
static void	calculate_specular(t_phong_helper *p);

/**
 * @returns	Color defined by phong helper p
 */
t_color	let_there_be_light(t_phong_helper *p)
{
	t_ray		shadow_ray;
	t_flt const	ab = get_data()->elems.ambient_light->brightness;

	if (dot(p->to_cam, p->normal) < 0)
		p->normal = opposite_vec(p->normal);
	p->ambient = scaled_vec(p->mat->color, ab);
	p->to_light = unit_vec(vec_sub(p->light->pos, p->pos));
	shadow_ray = (t_ray){.orig = p->pos, .dir = p->to_light};
	cast_ray_at_objs(&shadow_ray, &get_data()->elems, p->obj_hit);
	if (shadow_ray.intersections.idx == 0)
		calculate_diffuse_and_specular(p);
	else
	{
		p->diffuse = (t_vec4){0};
		p->specular = (t_vec4){0};
	}
	p->combined = vec_sum(vec_sum(p->ambient, p->diffuse), p->specular);
	free(shadow_ray.intersections._);
	return (vec4_to_color(p->combined));
}

/**
 * Calculates diffuse based on phong helper p and calls specular calculation
 * function.
 */
static void	calculate_diffuse_and_specular(t_phong_helper *p)
{
	p->surface_light_alignment = dot(p->to_light, p->normal);
	if (p->surface_light_alignment < 0)
	{
		p->diffuse = (t_vec4){0};
		p->specular = (t_vec4){0};
		return ;
	}
	p->effective_color = scaled_vec(p->mat->color, p->light->brightness);
	p->diffuse = scaled_vec(p->effective_color,
			p->mat->diffuse * p->surface_light_alignment);
	calculate_specular(p);
}

/**
 * Calculates specular based on phong helper p
 */
static void	calculate_specular(t_phong_helper *p)
{
	t_flt	f;

	p->from_light = scaled_vec(p->to_light, -1);
	p->ref = reflection(p->from_light, p->normal);
	p->camera_reflection_alignment = dot(p->to_cam, p->ref);
	if (p->camera_reflection_alignment < 0)
	{
		p->specular = (t_vec4){0};
		return ;
	}
	p->scaled_light = (t_vec4){
		.x = p->light->color.flt.r,
		.y = p->light->color.flt.g,
		.z = p->light->color.flt.b,
		.w = p->light->color.flt.a};
	p->scaled_light = scaled_vec(p->scaled_light, p->light->brightness);
	f = pow(p->camera_reflection_alignment, p->mat->shininess);
	p->specular = scaled_vec(p->scaled_light, p->mat->specular * f);
}
