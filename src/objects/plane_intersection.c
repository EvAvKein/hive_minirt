/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:41:38 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/23 13:15:24 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param ray	Ray struct to cast at plane
 * @param pl	Plane struct pointer to cast ray at
 *
 * @returns	Ray x object struct containing plane intersection, 0 struct if no
 *			valid intersection could be found
 */
t_ray_x_obj	ray_x_plane(t_ray ray, t_plane const *pl)
{
	t_flt	t;
	t_flt	divisor;

	ray = transformed_ray(ray, pl->inverse);
	divisor = dot(ray.dir, vector(0, 1, 0));
	if (floats_are_equal(divisor, 0))
		return ((t_ray_x_obj){0});
	t = dot(vec_sub(pl->pos, ray.orig), vector(0, 1, 0)) / divisor;
	if (t < 0)
		return ((t_ray_x_obj){0});
	return ((t_ray_x_obj){.t = t, .obj = (void *)pl, .obj_type = PLANE});
}

/**
 * @param ray	Ray struct to cast at plane
 * @param pl	Plane struct pointer to cast ray at
 *
 * @returns	Plane normal
 */
t_vec4	plane_normal(t_plane pl)
{
	t_vec4	normal;

	return (pl.orientation);
	normal = transformed_vec(pl.orientation, pl.inverse);
	normal = unit_vec(transformed_vec(normal, transpose_m4x4(pl.inverse)));
	normal.w = 0;
	return (normal);
}
