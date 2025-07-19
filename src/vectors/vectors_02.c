/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:51:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/08 10:09:46 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Dot product of vectors v1 and v2
 */
inline t_flt	dot(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x
		+ v1.y * v2.y
		+ v1.z * v2.z);
}

/**
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

/**
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

void	print_vec(t_vec4 vec)
{
	printf("Vec:	x = %f	y = %f	z = %f	w = %f\n",
		vec.x, vec.y, vec.z, vec.w);
}
