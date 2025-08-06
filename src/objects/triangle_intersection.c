/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:10:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/05 18:26:19 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param ray	Ray struct to cast at triangle
 * @param tr	Triangle struct pointer to cast ray at
 *
 * @returns	Ray x object struct containing triangle intersection, 0 struct if no
 *			valid intersection could be found
 */
t_ray_x_obj	ray_x_triangle(t_ray ray, t_triangle const *tr)
{
	t_vec4	edge1 = vec_sub(tr->pos2, tr->pos1);
	t_vec4	edge2 = vec_sub(tr->pos3, tr->pos1);
	t_vec4	ray_to_corner = vec_sub(ray.orig, tr->pos1);
	t_vec4	n = cross(edge1, edge2);
	t_vec4	q = cross(ray_to_corner, ray.dir);

	t_flt	d = 1.0f / dot(ray.dir, n);
	t_flt	u = d * dot(opposite_vec(q), edge2);
	t_flt	v = d * dot(q, edge1);
	t_flt	t = d * dot(opposite_vec(n), ray_to_corner);

	if (u < EPSILON || v < EPSILON || (u + v) > 1.0f)
		t = 0;
	return ((t_ray_x_obj){.t = t, .obj = (void *)tr, .obj_type = TRIANGLE});
}
