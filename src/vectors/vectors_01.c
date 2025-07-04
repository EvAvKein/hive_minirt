/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:10:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/04 10:52:16 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_flt	vec_len(t_vec4 const *vec)
{
	t_flt	len;

	len = sqrt(vec->axis.x * vec->axis.x
			+ vec->axis.y * vec->axis.y
			+ vec->axis.z * vec->axis.z);
	return (len);
}

t_vec4	new_unit_vec(t_vec4 const *vec)
{
	t_flt	len;
	t_flt	len_div;

	len = vec_len(vec);
	len_div = 1 / len;
	return (new_scaled_vec(vec, len_div));
}

t_vec4	*normalize_vec(t_vec4 *vec)
{
	t_flt	len;
	t_flt	len_div;

	len = vec_len(vec);
	len_div = 1 / len;
	return (scale_vec_in_place(vec, len_div));
}

t_vec4	new_scaled_vec(t_vec4 const *vec, t_flt scalar)
{
	return ((t_vec4)
		{._[0] = vec->_[0] * scalar,
		._[1] = vec->_[1] * scalar,
		._[2] = vec->_[2] * scalar,
		._[3] = vec->_[3]});
}

t_vec4	*scale_vec_in_place(t_vec4 *vec, t_flt scalar)
{
	vec->_[0] *= scalar;
	vec->_[1] *= scalar;
	vec->_[2] *= scalar;
	return (vec);
}
