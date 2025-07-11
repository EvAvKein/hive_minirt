/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:22:13 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/08 12:40:24 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Translation matrix based on the vector vec
 */
t_m4x4	translation_m4x4(t_vec4 vec)
{
	t_m4x4	translation;

	translation = identity_m4x4();
	translation._[0][3] = vec.axis.x;
	translation._[1][3] = vec.axis.y;
	translation._[2][3] = vec.axis.z;
	return (translation);
}

/**
 * @returns	Scaling matrix based on the vector vec
 */
t_m4x4	scaling_m4x4(t_vec4 vec)
{
	t_m4x4	scaling;

	scaling = identity_m4x4();
	scaling._[0][0] = vec.axis.x;
	scaling._[1][1] = vec.axis.y;
	scaling._[2][2] = vec.axis.z;
	return (scaling);
}

/**
 * @returns	X-rotation matrix, rotates vectors by deg degrees clockwise when
 *			the x-axis is pointing at the viewer
 */
t_m4x4	x_rotation_m4x4(t_flt deg)
{
	t_m4x4	rotation;

	rotation = identity_m4x4();
	rotation._[1][1] = cos(deg * RADIANS_PER_DEGREE);
	rotation._[1][2] = -sin(deg * RADIANS_PER_DEGREE);
	rotation._[2][1] = sin(deg * RADIANS_PER_DEGREE);
	rotation._[2][2] = cos(deg * RADIANS_PER_DEGREE);
	return (rotation);
}

/**
 * @returns	Y-rotation matrix, rotates vectors by deg degrees clockwise when
 *			the x-axis is pointing at the viewer
 */
t_m4x4	y_rotation_m4x4(t_flt deg)
{
	t_m4x4	rotation;

	rotation = identity_m4x4();
	rotation._[0][0] = cos(deg * RADIANS_PER_DEGREE);
	rotation._[0][2] = sin(deg * RADIANS_PER_DEGREE);
	rotation._[2][0] = -sin(deg * RADIANS_PER_DEGREE);
	rotation._[2][2] = cos(deg * RADIANS_PER_DEGREE);
	return (rotation);
}

/**
 * @returns	Z-rotation matrix, rotates vectors by deg degrees clockwise when
 *			the x-axis is pointing at the viewer
 */
t_m4x4	z_rotation_m4x4(t_flt deg)
{
	t_m4x4	rotation;

	rotation = identity_m4x4();
	rotation._[0][0] = cos(deg * RADIANS_PER_DEGREE);
	rotation._[0][1] = -sin(deg * RADIANS_PER_DEGREE);
	rotation._[1][0] = sin(deg * RADIANS_PER_DEGREE);
	rotation._[1][1] = cos(deg * RADIANS_PER_DEGREE);
	return (rotation);
}
