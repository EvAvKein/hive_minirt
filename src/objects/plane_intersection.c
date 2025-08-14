/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:41:38 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/13 17:26:55 by jvarila          ###   ########.fr       */
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

	ray = transformed_ray(ray, pl->inverse);
	if (flts_are_equal(ray.dir.y, 0))
		return ((t_ray_x_obj){});
	t = -ray.orig.y / ray.dir.y;
	if (t < EPSILON)
		return ((t_ray_x_obj){});
	return ((t_ray_x_obj){.t = t, .obj = (void *)pl, .obj_type = PLANE});
}
