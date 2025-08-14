/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:59:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/07 17:10:46 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec4	sphere_point_to_uv(t_vec4 vec);
static t_vec4	plane_point_to_uv(t_vec4 vec);
static t_vec4	cylinder_point_to_uv(t_vec4 vec, t_flt obj_height);
static t_vec4	cone_point_to_uv(t_vec4 vec, t_flt obj_height);

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
t_vec4	point_to_uv(t_obj_type type, t_vec4 point, t_flt obj_height)
{
	if (type == SPHERE)
		return (sphere_point_to_uv(point));
	if (type == PLANE)
		return (plane_point_to_uv(point));
	if (type == CYLINDER)
		return (cylinder_point_to_uv(point, obj_height));
	if (type == CONE)
		return (cone_point_to_uv(point, obj_height));
	return ((t_vec4){});
}

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

static t_vec4	cone_point_to_uv(t_vec4 vec, t_flt obj_height)
{
	vec.x = 0.5f + (atan2(vec.z, vec.x) / (2.0f * M_PI));
	vec.y = 0.5f + (vec.y / obj_height);
	return (vec);
}
