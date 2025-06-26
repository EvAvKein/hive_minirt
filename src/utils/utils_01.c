/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:47:07 by jvarila           #+#    #+#             */
/*   Updated: 2025/06/25 23:44:29 by jvarila          ###   ########.fr       */
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

bool	floats_are_equal(t_flt flt1, t_flt flt2)
{
	return (fabs(flt1 - flt2) < EPSILON);
}

bool	vecs_are_equal(t_vec4 const *vec1, t_vec4 const *vec2)
{
	return (floats_are_equal(vec1->_[0], vec2->_[0])
		&& floats_are_equal(vec1->_[1], vec2->_[1])
		&& floats_are_equal(vec1->_[2], vec2->_[2])
		&& floats_are_equal(vec1->_[3], vec2->_[3]));
}
