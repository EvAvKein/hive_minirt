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
	t_vec4	v1v0 = vec_sub(tr->pos2, tr->pos1);
	t_vec4	v2v0 = vec_sub(tr->pos3, tr->pos1);
	t_vec4	rov0 = vec_sub(ray.orig, tr->pos1);
	t_vec4	n = cross(v1v0, v2v0);
	t_vec4	q = cross(rov0, ray.dir);

	t_flt	d = 1.0f / dot(ray.dir, n);
	t_flt	u = d * dot(vec_sub((t_vec4){}, q), v2v0);
	t_flt	v = d * dot(q, v1v0);
	t_flt	t = d * dot(vec_sub((t_vec4){}, n), rov0);

	if (u < 0.0f || v < 0.0f || (u + v) > 1.0f)
		t = -1.0f;
	return ((t_ray_x_obj){.t = t, .obj = (void *)tr, .obj_type = TRIANGLE});
}
