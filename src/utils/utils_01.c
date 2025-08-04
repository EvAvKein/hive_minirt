/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:47:07 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 10:10:57 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Converts degrees into radians.
 *
 * @param degrees	Float value to convert into radians
 *
 * @returns	Angle in radians, converted from degrees
 */
inline t_flt	to_radians(t_flt degrees)
{
	return (degrees * RADIANS_PER_DEGREE);
}

/**
 * Converts radians into degrees.
 *
 * @param radians	Float value to convert into degrees
 *
 * @returns	Angle in degrees, converted from radians
 */
inline t_flt	to_degrees(t_flt radians)
{
	return (radians * DEGREES_PER_RADIAN);
}

/**
 * Function compares two floats, returns true if their difference is less
 * than EPSILON.
 *
 * @param flt1	First float to compare
 * @param flt2	Second float to compare
 *
 * @returns	true when the difference between the floats is less than EPSILON,
 *			false when the difference is equal or over
 */
inline bool	flts_are_equal(t_flt flt1, t_flt flt2)
{
	return (fabs(flt1 - flt2) < EPSILON);
}

/**
 * Function compares two vectors, returns true if the dimension values match
 * to the degree of EPSILON.
 *
 * @param vec1	First vector to compare
 * @param vec2	Second vector to compare
 *
 * @returns	true if all of the corresponding float pairs satisfy the function
 *			float_are_equal, false if not
 */
inline bool	vecs_are_equal(t_vec4 vec1, t_vec4 vec2)
{
	return (flts_are_equal(vec1.x, vec2.x)
		&& flts_are_equal(vec1.y, vec2.y)
		&& flts_are_equal(vec1.z, vec2.z)
		&& flts_are_equal(vec1.w, vec2.w));
}

/**
 * Function checks if a given vector points in the direction of the camera,
 * or if a given point is in front of the camera (same same but different).
 *
 * @param cam	Struct with camera information
 * @param vec	Vector to check
 *
 * @returns	true if the dot product with the camera direction is positive
 *			and above zero, false if negative
 */
inline bool	in_front_of_camera(t_camera cam, t_vec4 vec)
{
	return (dot(cam.orientation, vec) > 0);
}
