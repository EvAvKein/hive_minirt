/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:47:07 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/08 11:12:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Angle in radians, converted from degrees
 */
t_flt	to_radians(t_flt degrees)
{
	return (degrees * RADIANS_PER_DEGREE);
}

/**
 * @returns	Angle in degrees, converted from radians
 */
t_flt	to_degrees(t_flt radians)
{
	return (radians * DEGREES_PER_RADIAN);
}

/**
 * @returns	true when the difference between the floats is less than EPSILON,
 *			false when the difference is equal or over
 */
bool	floats_are_equal(t_flt flt1, t_flt flt2)
{
	return (fabs(flt1 - flt2) < EPSILON);
}

/**
 * @returns	true if all of the corresponding float pairs satisfy the function
 *			float_are_equal, false if not
 */
bool	vecs_are_equal(t_vec4 const *vec1, t_vec4 const *vec2)
{
	return (floats_are_equal(vec1->_[0], vec2->_[0])
		&& floats_are_equal(vec1->_[1], vec2->_[1])
		&& floats_are_equal(vec1->_[2], vec2->_[2])
		&& floats_are_equal(vec1->_[3], vec2->_[3]));
}

/**
 * @returns	true if the dot product with the camera direction is positive
 *			and above zero, false if negative
 */
bool	in_front_of_camera(t_camera const *cam, t_vec4 const *vec)
{
	if (dot(&cam->orientation, vec) > 0)
		return (true);
	return (false);
}
