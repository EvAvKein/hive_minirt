/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:17:56 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/11 14:36:42 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quad	solve_cone_quadratic(t_ray ray, t_cone cn);

t_ray_x_objs	ray_x_cone_shell(t_ray ray, t_cone const *cn)
{
	t_quad	q;
	t_flt	t[2];
	t_flt	y_component;

	ray = transformed_ray(ray, cn->inverse);
	q = solve_cone_quadratic(ray, *cn);
	if (flts_are_equal(q.a, 0) || q.discr < 0)
		return ((t_ray_x_objs){});
	t[0] = (-q.h - sqrt(q.discr)) / q.a;
	t[1] = (-q.h + sqrt(q.discr)) / q.a;
	y_component = ray_position(ray, t[0]).y;
	if (fabs(y_component) > cn->height - EPSILON)
		t[0] = 0;
	y_component = ray_position(ray, t[1]).y;
	if (fabs(y_component) > cn->height - EPSILON)
		t[1] = 0;
	return ((t_ray_x_objs){
		.count = 2,
		._[0] = (t_ray_x_obj){
		.obj_type = CONE, .obj = (void *)cn, .t = t[0]},
		._[1] = (t_ray_x_obj){
		.obj_type = CONE, .obj = (void *)cn, .t = t[1]}});
}

t_vec4	cone_normal_at(t_cone cn, t_vec4 world_pos)
{
	t_vec4	object_pos;
	t_vec4	normal;
	t_flt	r;

	object_pos = transformed_vec(world_pos, cn.inverse);
	if (flts_are_equal(fabs(object_pos.y), cn.height))
	{
		if (object_pos.y < 0)
			return (opposite_vec(cn.orientation));
		return (cn.orientation);
	}
	r = cn.diam / 2;
	normal = unit_vec(vector(object_pos.x, 0, object_pos.z));
	normal = scaled_vec(normal, r);
	normal.y = r * r / cn.height;
	if (object_pos.y > 0)
		normal.y *= -1;
	normal = unit_vec(transformed_vec(normal, transpose_m4x4(cn.inverse)));
	normal.w = 0;
	return (normal);
}

static t_quad	solve_cone_quadratic(t_ray ray, t_cone cn)
{
	t_quad	q;
	t_flt	r2;
	t_flt	h2;

	r2 = cn.diam / 2;
	r2 *= r2;
	h2 = cn.height * cn.height;
	q.a = h2 * (ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z)
		- r2 * ray.dir.y * ray.dir.y;
	if (flts_are_equal(q.a, 0))
		return ((t_quad){});
	q.h = h2 * (ray.dir.x * ray.orig.x + ray.dir.z * ray.orig.z)
		- r2 * ray.dir.y * ray.orig.y;
	q.c = h2 * (ray.orig.x * ray.orig.x + ray.orig.z * ray.orig.z)
		- r2 * ray.orig.y * ray.orig.y;
	q.discr = (q.h * q.h - q.a * q.c);
	return (q);
}
