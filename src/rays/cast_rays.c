/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:44:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/09 16:40:59 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	other_object_types(t_ray_x_obj *rxo, t_phong_helper *p);

/**
 * @returns	Struct containing the smallest non-negative t-valued intersection
 *			in rxos (ray-object intersections), 0 struct when both t-values
 *			are negative
 */
t_ray_x_obj	hit(t_ray_x_objs rxos)
{
	t_flt	t1;
	t_flt	t2;

	t1 = rxos._[0].t;
	t2 = rxos._[1].t;
	if ((flts_are_equal(t1, 0) && flts_are_equal(t2, 0))
		|| (t1 < 0 && t2 < 0))
		return ((t_ray_x_obj){});
	if (t1 < 0)
		return (rxos._[1]);
	if (t2 < 0)
		return (rxos._[0]);
	if (flts_are_equal(t1, 0))
		return (rxos._[1]);
	if (flts_are_equal(t2, 0))
		return (rxos._[0]);
	if (rxos._[0].t > rxos._[1].t)
		return (rxos._[1]);
	return (rxos._[0]);
}

/**
 * @returns The color at the provided intersection
 */
t_flt_color	color_at_obj_hit(t_ray_x_obj *rxo, t_phong_helper *p)
{
	if (rxo->obj_type == SPHERE)
	{
		p->normal = sphere_normal_at(*(t_sphere *)rxo->obj, p->pos);
		p->mat = mat_at_hit_on_sphere(&p->pos, (t_sphere *)p->obj_hit);
	}
	else if (rxo->obj_type == PLANE)
	{
		p->normal = ((t_plane *)rxo->obj)->orientation;
		p->mat = mat_at_hit_on_plane(&p->pos, (t_plane *)p->obj_hit);
	}
	else if (rxo->obj_type == CYLINDER)
	{
		p->normal = cylinder_normal_at(*(t_cylinder *)rxo->obj, p->pos);
		p->mat = mat_at_hit_on_cylinder(&p->pos, (t_cylinder *)p->obj_hit);
	}
	else if (rxo->obj_type == TRIANGLE)
	{
		p->normal = ((t_triangle *)rxo->obj)->normal;
		p->mat = mat_at_hit_on_triangle(&p->pos, (t_triangle *)p->obj_hit);
	}
	else
		other_object_types(rxo, p);
	if (rxo->obj_type == UNKNOWN)
		return ((t_flt_color){});
	return (let_there_be_light(p));
}

/**
 * TODO: Patterns for cones
 */
static void	other_object_types(t_ray_x_obj *rxo, t_phong_helper *p)
{
	if (rxo->obj_type == CONE)
	{
		p->normal = cone_normal_at(*(t_cone *)rxo->obj, p->pos);
		p->mat = ((t_cone *)p->obj_hit)->material;
	}
	else
		rxo->obj_type = UNKNOWN;
}
