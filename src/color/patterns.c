/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:08:40 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/27 13:47:55 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param relative_pos	The object-space position for which to calculate
 * 						the corresponding material
 *
 * @param mats			The object's own material and its pattern material
 *
 * @returns	The material at the provided position
 * 			according to our candy pattern
 */
t_material	mat_by_pattern_candy(
				t_vec4 relative_pos, t_pattern_mats mats)
{
	t_vec4				uv;

	uv = (t_vec4){
		.x = 0.5f + (atan2(relative_pos.z, relative_pos.x) / (2.0f * M_PI)),
		.y = 0.5f + (asin(relative_pos.y / vec_len(relative_pos)) / M_PI)
	};
	uv = percentagize_vec(uv);
	if ((((int)(uv.y) % 4) < 2 && ((int)(uv.x) % 4) >= 2)
		|| (((int)(uv.y) % 4) >= 2 && ((int)(uv.x) % 4) < 2))
	{
		if (uv.y < 0)
			return (mats.pat_mat);
		return (mats.obj_mat);
	}
	if (uv.y < 0)
		return (mats.obj_mat);
	return (mats.pat_mat);
}

/**
 * @param relative_pos	The object-space position for which to calculate
 * 						the corresponding material
 *
 * @param mats			The object's own material and its pattern material
 *
 * @returns	The material at the provided position
 * 			according to our circus pattern
 */
t_material	mat_by_pattern_circus(
				t_vec4 relative_pos, t_pattern_mats mats)
{
	t_flt				cross_axis;

	relative_pos = percentagize_vec((relative_pos));
	if (relative_pos.x > relative_pos.z)
		cross_axis = relative_pos.z;
	else
		cross_axis = relative_pos.x;
	if ((int)(cross_axis * relative_pos.y) / 250 % 2)
	{
		if (relative_pos.y < 0)
			return (mats.pat_mat);
		return (mats.obj_mat);
	}
	if (relative_pos.y < 0)
		return (mats.obj_mat);
	return (mats.pat_mat);
}

/**
 * @param relative_pos	The object-space position for which to calculate
 * 						the corresponding material
 *
 * @param mats			The object's own material and its pattern material
 *
 * @returns	The material at the provided position
 * 			according to our lines pattern
 */
t_material	mat_by_pattern_lines(t_vec4 relative_pos, t_pattern_mats mats)
{
	relative_pos = percentagize_vec(relative_pos);
	if ((int)(relative_pos.y / 8) % 2)
	{
		if (relative_pos.y < 0)
			return (mats.pat_mat);
		return (mats.obj_mat);
	}
	if (relative_pos.y < 0)
		return (mats.obj_mat);
	return (mats.pat_mat);
}

/**
 * @param relative_pos	The object-space position for which to calculate
 * 						the corresponding material
 *
 * @param mats			The object's own material and its pattern material
 *
 * @returns	The material at the provided position
 * 			according to our angel pattern
 */
t_material	mat_by_pattern_angel(t_vec4 relative_pos, t_pattern_mats mats)
{
	relative_pos = percentagize_vec(relative_pos);
	if (!((int)(relative_pos.y * 16) % 2))
	{
		if (relative_pos.y < 0)
			return (mats.pat_mat);
		return (mats.obj_mat);
	}
	if (relative_pos.y < 0)
		return (mats.obj_mat);
	return (mats.pat_mat);
}

t_material	mat_by_pattern_beams(t_vec4 relative_pos,
				t_pattern_mats mats, t_flt obj_height)
{
	const unsigned int	checker = 4;
	const unsigned int	pair = checker * 2;

	relative_pos.x = 0.5f
		+ (atan2(relative_pos.z, relative_pos.x) / (2.0f * M_PI));
	relative_pos.y = 0.5f + (relative_pos.y / obj_height);
	relative_pos = scaled_vec(relative_pos, 100);
	if (((int)(relative_pos.x) % pair) >= checker)
		return (mats.pat_mat);
	return (mats.obj_mat);
}
