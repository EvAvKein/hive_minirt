/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_checkerboard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:12:24 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/27 17:29:18 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec4	sphere_point_to_uv(t_vec4 vec)
{
	const t_flt	len = vec_len(vec);

	vec.x = 0.5f + (atan2(vec.z, vec.x) / (2.0f * M_PI));
	vec.y = 0.5f + (asin(vec.y / len) / M_PI);
	return (vec);
}

static t_vec4	plane_point_to_uv(t_vec4 vec)
{
	if (fabs(vec.x) < 0.1f)
		vec.x = 0;
	if (fabs(vec.z) < 0.1f)
		vec.z = 0;
	vec.x /= 128;
	vec.y = vec.z / 128;
	return (vec);
}

static t_vec4	cylinder_point_to_uv(t_vec4 vec, t_flt obj_height)
{
	vec.x = 0.5f + (atan2(vec.z, vec.x) / (2.0f * M_PI));
	vec.y = 0.5f + (vec.y / obj_height);
	return (vec);
}

/**
 * Converts the provided object-space point coordinates' `x` and `y`
 * to UV-mapped coordinates
 *
 * @param type			The type of object upon which to base the UV mapping
 *
 * @param point			The point (in object space) for UV mapping
 *
 * @param obj_height	The object's total height
 * 						(the distance between its lowest and highest Y)
 *
 * @returns The `point` vec,
 * 			with its `x` and `y` modified to UV-mapped coordinates
 */
static t_vec4	point_to_uv(t_obj_type type, t_vec4 point, t_flt obj_height)
{
	if (type == SPHERE)
		return (sphere_point_to_uv(point));
	if (type == PLANE)
		return (plane_point_to_uv(point));
	if (type == CYLINDER)
		return (cylinder_point_to_uv(point, obj_height));
	return ((t_vec4){0});
}

/**
 * TODO: Write these docs
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
