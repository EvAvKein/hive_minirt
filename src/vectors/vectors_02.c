/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:36:10 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/11 13:35:09 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param v1	First vector to use in dot product
 * @param v2	Second vector to use in dot product
 *
 * @returns	Dot product of vectors v1 and v2
 */
inline t_flt	dot(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x
		+ v1.y * v2.y
		+ v1.z * v2.z);
}

/**
 * @param v1	LHS vector to be used in cross product
 * @param v2	RHS vector to be used in cross product
 *
 * @returns	Left handed cross product of vectors v1 and v2, so a perpendicular
 *			vector to both v1 and v2
 */
t_vec4	cross(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){
		.x = v1.y * v2.z - v1.z * v2.y,
		.y = v1.z * v2.x - v1.x * v2.z,
		.z = v1.x * v2.y - v1.y * v2.x,
		.w = v1.w
	});
}

/**
 * @param vec	Vector to transform
 * @param t		Transformation matrix to multiply vec with
 *
 * @returns	The transformed vector resulting from vec being matrix multiplied
 *			by the transformatino matrix t
 */
t_vec4	transformed_vec(t_vec4 vec, t_m4x4 t)
{
	t_vec4	transformed;

	transformed.x = t._[0][0] * vec.x
		+ t._[0][1] * vec.y
		+ t._[0][2] * vec.z
		+ t._[0][3] * vec.w;
	transformed.y = t._[1][0] * vec.x
		+ t._[1][1] * vec.y
		+ t._[1][2] * vec.z
		+ t._[1][3] * vec.w;
	transformed.z = t._[2][0] * vec.x
		+ t._[2][1] * vec.y
		+ t._[2][2] * vec.z
		+ t._[2][3] * vec.w;
	transformed.w = t._[3][0] * vec.x
		+ t._[3][1] * vec.y
		+ t._[3][2] * vec.z
		+ t._[3][3] * vec.w;
	return (transformed);
}

/**
 * @param vec	Vector to create opposite from
 *
 * @returns	Vector pointing in the opposite direction than vec
 */
t_vec4	opposite_vec(t_vec4 vec)
{
	vec.x = -vec.x;
	vec.y = -vec.y;
	vec.z = -vec.z;
	return (vec);
}
