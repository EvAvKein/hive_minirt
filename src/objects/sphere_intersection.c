/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:14:55 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/09 14:12:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	true if the ray intersects the sphere, false if not
 *
 * @todo	Consider adding support for sphere transform matrices
 */
bool	ray_intersects_sphere(t_ray const *ray, t_sphere const *sp)
{
	t_quad	q;

	q = solve_sphere_quadratic(ray, sp);
	if (q.discr >= 0)
		return (true);
	return (false);
}

/**
 * @returns	Struct with two ray-object intersections, defined by t values
 *			(how long to follow the ray and in which direction), and an
 *			object flag combined with a void pointer to that object's data
 * @todo	Consider adding support for sphe sgre transform matrices
 */
t_rxos	ray_x_sphere(t_ray const *ray, t_sphere const *sp)
{
	t_quad	q;
	t_flt	t1;
	t_flt	t2;

	q = solve_sphere_quadratic(ray, sp);
	if (q.discr < 0)
		return ((t_rxos){0});
	t1 = (-q.b + sqrt(q.discr)) / (2 * q.a);
	t2 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	return ((t_rxos){
		.count = 2,
		._[0] = (t_rxo){.obj_type = SPHERE, .obj = (void *)sp, .t = t1},
		._[1] = (t_rxo){.obj_type = SPHERE, .obj = (void *)sp, .t = t2}});
}

/**
 * @returns	Struct containing the smallest non-negative t-valued intersection
 *			in rxos (ray-object intersections), 0 struct when both t-values
 *			are negative
 *
 * @todo	Consider adding support for sphere transform matrices
 */
t_rxo	hit(t_rxos const *rxos)
{
	if (rxos->_[0].t < 0 && rxos->_[1].t < 0)
		return ((t_rxo){0});
	if (rxos->_[0].t < 0)
		return (rxos->_[1]);
	if (rxos->_[1].t > 0
		&& rxos->_[0].t > rxos->_[1].t)
		return (rxos->_[1]);
	return (rxos->_[0]);
}

/**
 * @returns	Sphere's normal at ray's intersection rxo
 *
 * @todo	Consider adding support for sphere transform matrices
 */
t_vec4	sphere_normal_at(t_sphere const *sp, t_ray const *ray, t_rxo const *rxo)
{
	t_vec4	normal;
	t_vec4	intersection_position;
	t_vec4	ray_origin;
	t_vec4	ray_traversal;

	ray_origin = ray->orig;
	ray_traversal = scaled_vec(&ray->dir, rxo->t);
	intersection_position = vec_sum(&ray_origin, &ray_traversal);
	normal = vec_sub(&intersection_position, &sp->pos);
	normalize_vec(&normal);
	return (normal);
}
