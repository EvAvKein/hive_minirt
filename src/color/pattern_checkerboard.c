/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_checkerboard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:12:24 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/07 17:01:13 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param relative_pos	The object-space position for which to calculate
 * 						the corresponding material
 *
 * @param mats			The object's own material and its pattern material
 *
 * @param obj_type		The type of object it is
 *
 * @param obj_height	The object's total height
 * 						(the distance between its lowest and highest Y)
 *
 * @returns	The material at the provided position
 * 			according to the checkerboard pattern
 */
t_material	mat_by_pattern_checkerboard(t_vec4 relative_pos,
				t_pattern_mats mats, t_obj_type obj_type, t_flt obj_height)
{
	const unsigned int	checker = 4;
	const unsigned int	pair = checker * 2;

	relative_pos = point_to_uv(obj_type, relative_pos, obj_height);
	relative_pos = scaled_vec(relative_pos, 100);
	if ((((int)(relative_pos.y) % pair) < checker
		&& ((int)(relative_pos.x) % pair) >= checker)
		|| (((int)(relative_pos.y) % pair) >= checker
			&& ((int)(relative_pos.x) % pair) < checker))
		return (mats.pat_mat);
	return (mats.obj_mat);
}
