/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:36:10 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/28 10:15:33 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
 * @param vec	Vector to normalize to the range 0-100
 *
 * @returns		A 0-100 normalized version of the provided vector
 */
t_vec4	percentagize_vec(t_vec4 vec)
{
	vec = unit_vec(vec);
	vec = scaled_vec(vec, 100);
	return (vec);
}
