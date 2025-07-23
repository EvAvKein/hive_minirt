/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:01:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 10:56:57 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quad	solve_cylinder_quadratic(t_ray ray, t_cylinder cyl);

/**
 * @param ray	Ray struct that is cast at the cylinder
 * @param cyl	Cylinder struct pointer to cast the ray at
 *
 * @returns	Ray x object struct containing the hit information
 */
t_ray_x_obj	ray_hit_cylinder(t_ray ray, t_cylinder const *cyl)
{
	t_ray_x_objs	shell;
	t_ray_x_objs	caps;
	t_ray_x_objs	combined;
	t_ray_x_obj		primary_hit;

	shell = ray_x_cylinder_shell(ray, cyl);
	caps = ray_x_cylinder_caps(ray, cyl);
	combined = (t_ray_x_objs){._[0] = hit(shell), ._[1] = hit(caps)};
	primary_hit = hit(combined);
	return (primary_hit);
}

/**
 * @param ray	Ray struct that is cast at the cylinder
 * @param cyl	Cylinder struct pointer to cast the ray at
 *
 * @returns	Ray x objects struct containing the intersections with the cylinder
 *			shell
 */
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
	t2 = (-q.b + sqrt(q.discr)) / (2 * q.a);
	y_component = ray_position(ray, t1).y;
	if (fabs(y_component) > cyl->height / 2)
		t1 = 0;
	y_component = ray_position(ray, t2).y;
	if (fabs(y_component) > cyl->height / 2)
		t2 = 0;
	return ((t_ray_x_objs){
		.count = 2,
		._[0] = (t_ray_x_obj){
		.obj_type = CYLINDER, .obj = (void *)cyl, .t = t1},
		._[1] = (t_ray_x_obj){
		.obj_type = CYLINDER, .obj = (void *)cyl, .t = t2}});
}

/**
 * @param ray	Ray struct that is cast at the cylinder
 * @param cyl	Cylinder struct pointer to cast the ray at
 *
 * @returns	Ray x objects struct containing the intersections with the cylinder
 *			caps
 */
t_ray_x_objs	ray_x_cylinder_caps(t_ray ray, t_cylinder const *cyl)
{
	t_cap_helper	c;

	ray = transformed_ray(ray, cyl->inverse);
	c.top = (t_plane){.pos = point(0, cyl->height / 2, 0),
		.orientation = vector(0, 1, 0), .inverse = identity_m4x4()};
	c.btm = (t_plane){.pos = point(0, -cyl->height / 2, 0),
		.orientation = vector(0, -1, 0), .inverse = identity_m4x4()};
	c.top_hit = ray_x_plane(ray, &c.top);
	c.btm_hit = ray_x_plane(ray, &c.btm);
	c.top_mid = point(0, cyl->height / 2, 0);
	c.btm_mid = point(0, -cyl->height / 2, 0);
	c.top_mid_to_hit = vec_sub(ray_position(ray, c.top_hit.t), c.top_mid);
	c.btm_mid_to_hit = vec_sub(ray_position(ray, c.btm_hit.t), c.btm_mid);
	c.top_dist = vec_len(c.top_mid_to_hit);
	c.btm_dist = vec_len(c.btm_mid_to_hit);
	if (c.top_dist > cyl->diam / 2)
		c.top_hit.t = 0;
	if (c.btm_dist > cyl->diam / 2)
		c.btm_hit.t = 0;
	return ((t_ray_x_objs){.count = 2, ._[0] = (t_ray_x_obj){
		.obj_type = CYLINDER, .obj = (void *)cyl, .t = c.top_hit.t},
		._[1] = (t_ray_x_obj){
		.obj_type = CYLINDER, .obj = (void *)cyl, .t = c.btm_hit.t}});
}

/**
 * @param cyl		Cylinder struct
 * @param world_pos	Point in world coordinate space, on the surface of the
 *					cylinder
 *
 * @returns	Cylinder normal at given position
 */
t_vec4	cylinder_normal_at(t_cylinder cyl, t_vec4 world_pos)
{
	t_vec4	object_pos;
	t_vec4	normal;

	object_pos = transformed_vec(world_pos, cyl.inverse);
	if (floats_are_equal(fabs(object_pos.y), cyl.height / 2))
	{
		if (object_pos.y < 0)
			return (opposite_vec(cyl.orientation));
		return (cyl.orientation);
	}
	normal = vector(object_pos.x, 0, object_pos.z);
	normal = unit_vec(transformed_vec(normal, transpose_m4x4(cyl.inverse)));
	normal.w = 0;
	return (normal);
}

/**
 * Helper function to solve the quadratic equation that defines the cylinder
 * intersections.
 *
 * @param ray	Ray struct that is cast at the cylinder
 * @param cyl	Cylinder struct to cast the ray at
 *
 * @returns	t_quad helper struct containing the calculated second degree
 *			equation values, 0 struct if no valid solutions exist
 */
static t_quad	solve_cylinder_quadratic(t_ray ray, t_cylinder cyl)
{
	t_quad	q;

	q.a = pow(ray.dir.x, 2) + pow(ray.dir.z, 2);
	if (floats_are_equal(q.a, 0))
		return ((t_quad){0});
	q.b = 2 * ray.orig.x * ray.dir.x + 2 * ray.orig.z * ray.dir.z;
	q.c = pow(ray.orig.x, 2) + pow(ray.orig.z, 2) - pow(cyl.diam / 2, 2);
	q.discr = q.b * q.b - 4 * q.a * q.c;
	return (q);
}
