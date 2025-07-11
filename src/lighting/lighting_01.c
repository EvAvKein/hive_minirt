/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:50:49 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/11 10:56:04 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_diffuse_and_specular(t_phong_helper *p);
static void	calculate_specular(t_phong_helper *p);

t_color	let_there_be_light(t_phong_helper *p)
{
	t_color	color;

	p->effective_color = scaled_vec(p->mat->color, p->light->brightness);
	p->to_light = unit_vec(vec_sub(p->light->pos, p->pos));
	p->ambient = scaled_vec(p->effective_color, p->mat->ambient);
	calculate_diffuse_and_specular(p);
	p->combined = vec_sum(vec_sum(p->ambient, p->diffuse), p->specular);
	color = vec4_to_color(p->combined);
	return (color);
}

static void	calculate_diffuse_and_specular(t_phong_helper *p)
{
	p->surface_light_alignment = dot(p->to_light, p->normal);
	if (p->surface_light_alignment < 0)
	{
		p->diffuse = (t_vec4){0};
		p->specular = (t_vec4){0};
		return ;
	}
	p->diffuse = scaled_vec(p->effective_color,
			p->mat->diffuse * p->surface_light_alignment);
	calculate_specular(p);
}

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
		._[0] = p->light->color.flt.r,
		._[1] = p->light->color.flt.g,
		._[2] = p->light->color.flt.b,
		._[3] = p->light->color.flt.a};
	p->scaled_light = scaled_vec(p->scaled_light, p->light->brightness);
	f = pow(p->camera_reflection_alignment, p->mat->shininess);
	p->specular = scaled_vec(p->scaled_light, p->mat->specular * f);
}
