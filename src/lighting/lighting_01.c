/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:50:49 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 15:25:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_diffuse_and_specular(t_phong_helper *p);
static void	calculate_specular(t_phong_helper *p);
static void	set_ambient(t_phong_helper *p);

/**
 * @param p	Phong helper struct
 *
 * @returns	Color defined by phong helper p
 */
t_flt_color	let_there_be_light(t_phong_helper *p)
{
	t_ray		shadow_ray;

	p->light = g_data.elems.lights;
	if (dot(p->to_cam, p->normal) < 0)
	{
		p->normal = opposite_vec(p->normal);
		p->obj_hit = NULL;
	}
	set_ambient(p);
	while (p->light)
	{
		p->to_light = unit_vec(vec_sub(p->light->pos, p->pos));
		shadow_ray = (t_ray){.orig = p->pos, .dir = p->to_light,
			.closest_hit.t = MAX_DIST};
		cast_ray_at_objs(&shadow_ray, &g_data.elems, p->obj_hit);
		p->dist_to_light = vec_len(vec_sub(p->light->pos, p->pos));
		if (shadow_ray.closest_hit.t == MAX_DIST
			|| shadow_ray.closest_hit.t > p->dist_to_light)
			calculate_diffuse_and_specular(p);
		p->light = p->light->next;
	}
	p->combined = vec_sum(p->ambient, vec_sum(p->diffuse, p->specular));
	return (p->combined);
}

/**
 * Sets phong helper's ambient light component.
 *
 * @param p	Phong helper struct pointer
 */
static void	set_ambient(t_phong_helper *p)
{
	t_flt const			ab_intensity = g_data.elems.ambient_light->brightness;
	t_flt_color const	ab_color = g_data.elems.ambient_light->color;

	p->ambient = (t_flt_color){
		.r = ab_intensity * p->mat.color.r * ab_color.r,
		.g = ab_intensity * p->mat.color.g * ab_color.g,
		.b = ab_intensity * p->mat.color.b * ab_color.b,
		.a = 1
	};
}

/**
 * Calculates diffuse based on phong helper p and calls specular calculation
 * function.
 *
 * @param p	Phong helper struct
 */
static void	calculate_diffuse_and_specular(t_phong_helper *p)
{
	p->surface_light_alignment = dot(p->to_light, p->normal);
	if (p->surface_light_alignment < 0)
		return ;
	p->effective_color = (t_flt_color){
		.r = p->mat.color.r * p->light->brightness * p->light->color.r,
		.g = p->mat.color.g * p->light->brightness * p->light->color.g,
		.b = p->mat.color.b * p->light->brightness * p->light->color.b,
		.a = 1
	};
	p->diffuse = vec_sum(p->diffuse, scaled_vec(p->effective_color,
				p->mat.diffuse * p->surface_light_alignment));
	calculate_specular(p);
}

/**
 * Calculates specular based on phong helper p
 *
 * @param p	Phong helper struct
 */
static void	calculate_specular(t_phong_helper *p)
{
	t_flt	f;

	p->from_light = scaled_vec(p->to_light, -1);
	p->ref = reflection(p->from_light, p->normal);
	p->camera_reflection_alignment = dot(p->to_cam, p->ref);
	if (p->camera_reflection_alignment < 0)
		return ;
	p->scaled_light = point(
			p->light->color.r, p->light->color.g, p->light->color.g);
	p->scaled_light = scaled_vec(p->scaled_light, p->light->brightness);
	f = pow(p->camera_reflection_alignment, p->mat.shininess);
	p->specular = vec_sum(p->specular, scaled_vec(p->scaled_light,
				p->mat.specular * f));
}
