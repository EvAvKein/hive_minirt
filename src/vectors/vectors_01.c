/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:10:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/08 10:09:30 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
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
 * @returns	Unit vector based on vec
 */
t_vec4	unit_vec(t_vec4 vec)
{
	t_flt	len;
	t_flt	len_div;

	vec.w = 0;
	len = vec_len(vec);
	len_div = 1 / len;
	return (scaled_vec(vec, len_div));
}

/**
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
 * @returns	New t_vec4 struct with the given floats as dimensions, w set to 1
 */
t_vec4	position(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.x = x,
		.y = y,
		.z = z,
		.w = 1});
}
