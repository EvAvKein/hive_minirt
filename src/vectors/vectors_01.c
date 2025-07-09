/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:10:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/08 10:09:30 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Length of vector parameter vec
 */
t_flt	vec_len(t_vec4 const *vec)
{
	t_flt	len;

	len = sqrt(vec->axis.x * vec->axis.x
			+ vec->axis.y * vec->axis.y
			+ vec->axis.z * vec->axis.z);
	return (len);
}

/**
 * @returns	Unit vector based on vec
 */
t_vec4	unit_vec(t_vec4 const *vec)
{
	t_flt	len;
	t_flt	len_div;

	len = vec_len(vec);
	len_div = 1 / len;
	return (scaled_vec(vec, len_div));
}

/**
 * Normalizes vec in place, aka divides each dimension by the length of vec,
 * turning it into a unit vector, and returns its address
 *
 * @returns	Address of vec
 */
t_vec4	*normalize_vec(t_vec4 *vec)
{
	t_flt	len;
	t_flt	len_div;

	len = vec_len(vec);
	len_div = 1 / len;
	return (scale_vec(vec, len_div));
}

/**
 * @returns	Scaled vector, whose dimensions are the dimensions of vec scaled
 *			by scalar
 */
t_vec4	scaled_vec(t_vec4 const *vec, t_flt scalar)
{
	return ((t_vec4){
		._[0] = vec->_[0] * scalar,
		._[1] = vec->_[1] * scalar,
		._[2] = vec->_[2] * scalar,
		._[3] = vec->_[3]});
}

/**
 * Scales vector in place
 *
 * @returns	Address of vec
 */
t_vec4	*scale_vec(t_vec4 *vec, t_flt scalar)
{
	vec->_[0] *= scalar;
	vec->_[1] *= scalar;
	vec->_[2] *= scalar;
	return (vec);
}
