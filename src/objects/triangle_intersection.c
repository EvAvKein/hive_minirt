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

static t_vec4	triangle_math_pt2(t_vec4 edge1, t_vec4 edge2,
					t_vec4 ray_to_corner, t_vec4 q);

/**
 * @param ray	Ray struct to cast at triangle
 * @param tr	Triangle struct pointer to cast ray at
 *
 * @returns	Ray x object struct containing triangle intersection, 0 struct if no
 *			valid intersection could be found
 */
t_ray_x_obj	ray_x_triangle(t_ray ray, t_triangle const *tr)
{
	const t_vec4	edge1 = vec_sub(tr->pos2, tr->pos1);
	const t_vec4	edge2 = vec_sub(tr->pos3, tr->pos1);
	const t_vec4	ray_to_corner = vec_sub(ray.orig, tr->pos1);
	t_vec4			math;

	math = triangle_math_pt2(edge1, edge2,
			ray_to_corner, ray.dir);
	if (math.x < EPSILON || math.y < EPSILON || (math.x + math.y) > 1.0f)
		math.z = 0;
	return ((t_ray_x_obj){
		.t = math.z, .obj = (void *)tr, .obj_type = TRIANGLE});
}

static t_vec4	triangle_math_pt2(t_vec4 edge1, t_vec4 edge2,
					t_vec4 ray_to_corner, t_vec4 ray_dir)
{
	const t_vec4	q = cross(ray_to_corner, ray_dir);
	const t_vec4	n = cross(edge1, edge2);
	const t_flt		d = 1.0f / dot(ray_dir, n);

	return ((t_vec4){
		.x = d * dot(opposite_vec(q), edge2),
		.y = d * dot(q, edge1),
		.z = d * dot(opposite_vec(n), ray_to_corner)});
}
