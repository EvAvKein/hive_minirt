/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:14:55 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/16 10:32:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quad	solve_sphere_quadratic(t_ray ray, t_sphere sp);

/**
 * @returns	Struct with two ray-object intersections, defined by t values
 *			(how long to follow the ray and in which direction), and an
 *			object flag combined with a void pointer to that object's data
 */
t_ray_x_objs	ray_x_sphere(t_ray ray, t_sphere const *sp)
{
	t_quad	q;
	t_flt	t1;
	t_flt	t2;

	ray = transformed_ray(ray, sp->inverse);
	q = solve_sphere_quadratic(ray, *sp);
	if (q.discr < 0)
		return ((t_ray_x_objs){0});
	t1 = (-q.b + sqrt(q.discr)) / (2 * q.a);
	t2 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	return ((t_ray_x_objs){
		.count = 2,
		._[0] = (t_ray_x_obj){.obj_type = SPHERE, .obj = (void *)sp, .t = t1},
		._[1] = (t_ray_x_obj){.obj_type = SPHERE, .obj = (void *)sp, .t = t2}});
}

/**
 * @returns	t_quad helper struct which contains the values for solving a
 *			quadratic equation.
 */
static t_quad	solve_sphere_quadratic(t_ray ray, t_sphere sp)
{
	t_quad	q;

	q.a = dot(ray.dir, ray.dir);
	q.b = 2 * dot(ray.dir, ray.orig);
	q.c = dot(ray.orig, ray.orig) - sp.radius * sp.radius;
	q.discr = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

/**
 * @returns	Sphere's normal at ray's intersection rxo
 */
t_vec4	sphere_normal_at(t_sphere sp, t_vec4 world_pos)
{
	t_vec4	normal;
	t_vec4	object_pos;

	object_pos = transformed_vec(world_pos, sp.inverse);
	normal = unit_vec(transformed_vec(object_pos, transpose_m4x4(sp.inverse)));
	normal.axis.w = 0;
	return (normal);
}
