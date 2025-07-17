/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:01:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/17 11:59:48 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quad	solve_cylinder_quadratic(t_ray ray, t_cylinder cyl)
{
	t_quad	q;

	q.a = pow(ray.dir._[0], 2) + pow(ray.dir._[2], 2);
	if (floats_are_equal(q.a, 0))
		return ((t_quad){0});
	q.b = 2 * ray.orig._[0] * ray.dir._[0] + 2 * ray.orig._[2] * ray.dir._[2];
	q.c = pow(ray.orig._[0], 2) + pow(ray.orig._[2], 2) - pow(cyl.diam / 2, 2);
	q.discr = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

bool	ray_hits_cylinder(t_ray ray, t_cylinder cyl)
{
	t_quad	q;
	t_flt	t1;
	t_flt	t2;
	t_flt	y_component;

	q.a = pow(ray.dir._[0], 2) + pow(ray.dir._[2], 2);
	if (floats_are_equal(q.a, 0))
		return (false);
	q.b = 2 * ray.orig._[0] * ray.dir._[0] + 2 * ray.orig._[2] * ray.dir._[2];
	q.c = pow(ray.orig._[0], 2) + pow(ray.orig._[2], 2) - pow(cyl.diam / 2, 2);
	q.discr = q.b * q.b - 4 * q.a * q.c;
	if (q.discr < 0)
		return (false);
	t1 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	t2 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	y_component = dot(ray_position(ray, t1), vector(0, 1, 0));
	if (fabs(y_component) > cyl.height / 2)
		t1 = 0;
	y_component = dot(ray_position(ray, t2), vector(0, 1, 0));
	if (fabs(y_component) > cyl.height / 2)
		t2 = 0;
	return (!floats_are_equal(t1, 0) || !floats_are_equal(t2, 0));
}

t_ray_x_objs	ray_x_cylinder_shell(t_ray ray, t_cylinder const *cyl)
{
	t_quad	q;
	t_flt	t1;
	t_flt	t2;
	t_flt	y_component;

	ray = transformed_ray(ray, cyl->inverse);
	q = solve_cylinder_quadratic(ray, *cyl);
	if (floats_are_equal(q.a, 0) || q.discr < 0)
		return ((t_ray_x_objs){0});
	t1 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	t2 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	y_component = dot(ray_position(ray, t1), vector(0, 1, 0));
	if (fabs(y_component) > cyl->height / 2)
		t1 = 0;
	y_component = dot(ray_position(ray, t2), vector(0, 1, 0));
	if (fabs(y_component) > cyl->height / 2)
		t2 = 0;
	return ((t_ray_x_objs){
		.count = 2,
		._[0] = (t_ray_x_obj){
		.obj_type = CYLINDER, .obj = (void *)cyl, .t = t1},
		._[1] = (t_ray_x_obj){
		.obj_type = CYLINDER, .obj = (void *)cyl, .t = t2}});
}
