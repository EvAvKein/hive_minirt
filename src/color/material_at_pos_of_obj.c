/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_at_pos_of_obj.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:05:00 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/27 13:44:45 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns The material at this position of the sphere
 */
t_material	material_at_hit_on_sphere(t_vec4 *hit_pos, t_sphere *sphere)
{
	const t_vec4	relative_pos = transformed_vec(*hit_pos, sphere->inverse);

	if (sphere->pattern == SOLID)
		return (sphere->material);
	else if (sphere->pattern == CHECKERBOARD)
		return (mat_by_pattern_checkerboard(relative_pos,
				sp_pattern_mats(CHECKERBOARD, sphere),
				SPHERE, sphere->radius * 2));
	else if (sphere->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				sp_pattern_mats(CANDY, sphere)));
	else if (sphere->pattern == CIRCUS)
		return (mat_by_pattern_circus(relative_pos,
				sp_pattern_mats(CIRCUS, sphere)));
	else if (sphere->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				sp_pattern_mats(LINES, sphere)));
	else if (sphere->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				sp_pattern_mats(ANGEL, sphere)));
	else if (sphere->pattern == BEAMS)
		return (mat_by_pattern_beams(relative_pos,
				sp_pattern_mats(BEAMS, sphere),
				sphere->radius * 2));
	return (sphere->material);
}

/**
 * @returns The material at this position of the plane
 */
t_material	material_at_hit_on_plane(t_vec4 *hit_pos, t_plane *plane)
{
	const t_vec4	relative_pos = transformed_vec(*hit_pos, plane->inverse);

	if (plane->pattern == SOLID)
		return (plane->material);
	else if (plane->pattern == CHECKERBOARD)
		return (mat_by_pattern_checkerboard(relative_pos,
				pl_pattern_mats(CHECKERBOARD, plane), PLANE, 1));
	else if (plane->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				pl_pattern_mats(CANDY, plane)));
	else if (plane->pattern == CIRCUS)
		return (mat_by_pattern_circus(relative_pos,
				pl_pattern_mats(CIRCUS, plane)));
	else if (plane->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				pl_pattern_mats(LINES, plane)));
	else if (plane->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				pl_pattern_mats(ANGEL, plane)));
	else if (plane->pattern == BEAMS)
		return (mat_by_pattern_beams(relative_pos,
				pl_pattern_mats(BEAMS, plane), 1));
	return (plane->material);
}

/**
 * @returns The material at this position of the cylinder
 */
t_material	material_at_hit_on_cylinder(t_vec4 *hit_pos, t_cylinder *cylinder)
{
	const t_vec4	relative_pos = transformed_vec(*hit_pos, cylinder->inverse);

	if (cylinder->pattern == SOLID)
		return (cylinder->material);
	else if (cylinder->pattern == CHECKERBOARD)
		return (mat_by_pattern_checkerboard(relative_pos,
				cy_pattern_mats(CHECKERBOARD, cylinder),
				CYLINDER, cylinder->height));
	else if (cylinder->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				cy_pattern_mats(BEAMS, cylinder)));
	else if (cylinder->pattern == CIRCUS)
		return (mat_by_pattern_circus(relative_pos,
				cy_pattern_mats(CIRCUS, cylinder)));
	else if (cylinder->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				cy_pattern_mats(LINES, cylinder)));
	else if (cylinder->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				cy_pattern_mats(ANGEL, cylinder)));
	else if (cylinder->pattern == BEAMS)
		return (mat_by_pattern_beams(relative_pos,
				cy_pattern_mats(BEAMS, cylinder),
				cylinder->height));
	return (cylinder->material);
}
