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
		return ((t_vec4){});
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
 * @param v1	First vector to use in addition
 * @param v2	Second vector to use in addition
 *
 * @returns	Vector whose three first dimensions are the sums of the
 *			corresponding dimensions of v1 and v2, the fourth dimension
 *			is left as is from v1
 */
t_vec4	vec_sum(t_vec4 v1, t_vec4 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

/**
 * @param v1	Vector to subtract from
 * @param v2	Vector to subtract with
 *
 * @returns	Vector whose three first dimensions are the differences of the
 *			corresponding dimensions of v1 and v2, the fourth dimension
 *			is left as is from v1
 */
t_vec4	vec_sub(t_vec4 v1, t_vec4 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}
