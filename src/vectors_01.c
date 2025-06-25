/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:10:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/06/25 21:15:21 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_flt	vector_len(t_vec4 const *vec)
{
	t_flt	len;

	len = sqrt(vec->axis.x * vec->axis.x
			+ vec->axis.y * vec->axis.y
			+ vec->axis.z * vec->axis.z);
	return (len);
}

t_vec4	new_unit_vector(const t_vec4 *vec)
{
	t_vec4	uvec;
	t_flt	len;

	len = vector_len(vec);
	uvec.axis.x = vec->axis.x / len;
	uvec.axis.y = vec->axis.y / len;
	uvec.axis.z = vec->axis.z / len;
	uvec.axis.w = 0;
	return (uvec);
}

t_vec4	*normalize_vector(t_vec4 *vec)
{
	t_flt	len;

	len = vector_len(vec);
	vec->axis.x /= len;
	vec->axis.y /= len;
	vec->axis.z /= len;
	vec->axis.w = 0;
	return (vec);
}
