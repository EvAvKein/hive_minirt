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
t_flt	dot(t_vec4 v1, t_vec4 v2)
{
	return (v1._[0] * v2._[0]
		+ v1._[1] * v2._[1]
		+ v1._[2] * v2._[2]);
}

/**
 * @returns	Vector whose three first dimensions are the sums of the
 *			corresponding dimensions of v1 and v2, the fourth dimension
 *			is left as is from v1
 */
t_vec4	vec_sum(t_vec4  v1, t_vec4 v2)
{
	v1._[0] += v2._[0];
	v1._[1] += v2._[1];
	v1._[2] += v2._[2];
	return (v1);
}

/**
 * @returns	Vector whose three first dimensions are the differences of the
 *			corresponding dimensions of v1 and v2, the fourth dimension
 *			is left as is from v1
 */
t_vec4	vec_sub(t_vec4 v1, t_vec4 v2)
{
	v1._[0] -= v2._[0];
	v1._[1] -= v2._[1];
	v1._[2] -= v2._[2];
	return (v1);
}

/**
 * @returns	The transformed vector resulting from vec being matrix multiplied
 *			by the transformatino matrix t
 */
t_vec4	transformed_vec(t_vec4 vec, t_m4x4 t)
{
	t_vec4	transformed;

	transformed.axis.x = t._[0][0] * vec._[0]
		+ t._[0][1] * vec._[1]
		+ t._[0][2] * vec._[2]
		+ t._[0][3] * vec._[3];
	transformed.axis.y = t._[1][0] * vec._[0]
		+ t._[1][1] * vec._[1]
		+ t._[1][2] * vec._[2]
		+ t._[1][3] * vec._[3];
	transformed.axis.z = t._[2][0] * vec._[0]
		+ t._[2][1] * vec._[1]
		+ t._[2][2] * vec._[2]
		+ t._[2][3] * vec._[3];
	transformed.axis.w = t._[3][0] * vec._[0]
		+ t._[3][1] * vec._[1]
		+ t._[3][2] * vec._[2]
		+ t._[3][3] * vec._[3];
	return (transformed);
}

void	print_vec(t_vec4 vec)
{
	printf("Vec:	x = %f	y = %f	z = %f	w = %f\n",
		vec.axis.x, vec.axis.y, vec.axis.z, vec.axis.w);
}
