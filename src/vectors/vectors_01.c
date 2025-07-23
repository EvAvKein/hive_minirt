/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:10:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 10:47:20 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param vec	Vector to measure
 *
 * @returns	Length of vector parameter vec
 */
t_flt	vec_len(t_vec4 vec)
{
	t_flt	len;

	len = sqrt(vec.x * vec.x
			+ vec.y * vec.y
			+ vec.z * vec.z);
	return (len);
}

/**
 * @param vec	Vector to create unit vector from
 *
 * @returns	Unit vector based on vec
 */
t_vec4	unit_vec(t_vec4 vec)
{
	t_flt	len;
	t_flt	len_div;

	vec.w = 0;
	len = vec_len(vec);
	if (len == 0)
		return ((t_vec4){0});
	len_div = 1 / len;
	return (scaled_vec(vec, len_div));
}

/**
 * @param vec		Vector to scale
 * @param scalar	Float to scale the vector by
 *
 * @returns	Scaled vector, whose dimensions are the dimensions of vec scaled
 *			by scalar
 */
t_vec4	scaled_vec(t_vec4 vec, t_flt scalar)
{
	vec.x *= scalar;
	vec.y *= scalar;
	vec.z *= scalar;
	return (vec);
}

/**
 * @param x	Float to be used as the x axis of the vector
 * @param y	Float to be used as the y axis of the vector
 * @param z	Float to be used as the z axis of the vector
 *
 * @returns	New t_vec4 struct with the given floats as dimensions, w set to 0
 */
t_vec4	vector(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.x = x,
		.y = y,
		.z = z,
		.w = 0});
}

/**
 * @param x	Float to be used as the x axis of the position
 * @param y	Float to be used as the y axis of the position
 * @param z	Float to be used as the z axis of the position
 *
 * @returns	New t_vec4 struct with the given floats as dimensions, w set to 1
 */
t_vec4	point(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.x = x,
		.y = y,
		.z = z,
		.w = 1});
}
