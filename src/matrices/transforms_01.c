/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:22:13 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 18:38:15 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Creates a matrix that translates (moves) points by the vector vec. Vectors
 * with dimension w = 0 are unaffected by translations.
 *
 * @param vec	Vector to base translation matrix on
 *
 * @returns	Translation matrix based on the vector vec
 */
t_m4x4	translation_m4x4(t_vec4 vec)
{
	t_m4x4	translation;

	translation = identity_m4x4();
	translation._[0][3] = vec.x;
	translation._[1][3] = vec.y;
	translation._[2][3] = vec.z;
	return (translation);
}

/**
 * Creates a matrix that scales points and vectors by the vector vec. Keep each
 * dimension the same number for a uniform scaling.
 *
 * @param vec	Vector to base scaling matrix on
 *
 * @returns	Scaling matrix based on the vector vec
 */
t_m4x4	scaling_m4x4(t_vec4 vec)
{
	t_m4x4	scaling;

	scaling = identity_m4x4();
	scaling._[0][0] = vec.x;
	scaling._[1][1] = vec.y;
	scaling._[2][2] = vec.z;
	return (scaling);
}

/**
 * Creates a matrix that rotates points and vectors around the x axis.
 *
 * @param rad	Amount of radians to turn around the x axis
 *
 * @returns	X-rotation matrix, rotates vectors by rad radians clockwise when
 *			the x-axis is pointing at the viewer
 */
t_m4x4	x_rotation_m4x4(t_flt rad)
{
	t_m4x4	rotation;

	rotation = identity_m4x4();
	if (rad == 0)
		return (rotation);
	rotation._[1][1] = cos(rad);
	rotation._[1][2] = -sin(rad);
	rotation._[2][1] = sin(rad);
	rotation._[2][2] = cos(rad);
	return (rotation);
}

/**
 * Creates a matrix that rotates points and vectors around the y axis.
 *
 * @param rad	Amount of radians to turn around the y axis
 *
 * @returns	Y-rotation matrix, rotates vectors by rad radians clockwise when
 *			the x-axis is pointing at the viewer
 */
t_m4x4	y_rotation_m4x4(t_flt rad)
{
	t_m4x4	rotation;

	rotation = identity_m4x4();
	if (rad == 0)
		return (rotation);
	rotation._[0][0] = cos(rad);
	rotation._[0][2] = sin(rad);
	rotation._[2][0] = -sin(rad);
	rotation._[2][2] = cos(rad);
	return (rotation);
}

/**
 * Creates a matrix that rotates points and vectors around the z axis.
 *
 * @param rad	Amount of radians to turn around the z axis
 *
 * @returns	Z-rotation matrix, rotates vectors by rad radians clockwise when
 *			the x-axis is pointing at the viewer
 */
t_m4x4	z_rotation_m4x4(t_flt rad)
{
	t_m4x4	rotation;

	rotation = identity_m4x4();
	if (rad == 0)
		return (rotation);
	rotation._[0][0] = cos(rad);
	rotation._[0][1] = -sin(rad);
	rotation._[1][0] = sin(rad);
	rotation._[1][1] = cos(rad);
	return (rotation);
}
