/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:52:34 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 17:43:32 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns Whether the provided `checked`
 * is within the provided minimum and maximum (inclusive).
 */
inline bool	in_flt_range(t_flt checked, t_flt min, t_flt max)
{
	return (checked >= min && checked <= max);
}

/**
 * @returns Whether the provided vector's
 * x, y, and z axes are all between -1 and 1 (inclusive).
 */
inline bool	is_normalized_vec(t_vec4 vec)
{
	return (in_flt_range(vec.x, -1.f, 1.f)
		&& in_flt_range(vec.y, -1.f, 1.f)
		&& in_flt_range(vec.z, -1.f, 1.f));
}
