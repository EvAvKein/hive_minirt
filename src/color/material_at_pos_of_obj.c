/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_at_pos_of_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:05:00 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/05 17:14:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns The material at this position of the sphere
 */
t_material	mat_at_hit_on_sphere(t_vec4 *hit_pos, t_sphere *sp)
{
	const t_vec4	relative_pos = transformed_vec(*hit_pos, sp->inverse);

	if (sp->image)
		return (mat_by_texture_sphere(relative_pos, sp));
	else if (sp->pattern == SOLID)
		return (sp->material);
	else if (sp->pattern == CHECKERBOARD)
		return (mat_by_pattern_checkerboard(relative_pos,
				sp_pattern_mats(CHECKERBOARD, sp), SPHERE, sp->radius * 2));
	else if (sp->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				sp_pattern_mats(CANDY, sp)));
	else if (sp->pattern == CIRCUS)
		return (mat_by_pattern_circus(relative_pos,
				sp_pattern_mats(CIRCUS, sp)));
	else if (sp->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				sp_pattern_mats(LINES, sp)));
	else if (sp->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				sp_pattern_mats(ANGEL, sp)));
	else if (sp->pattern == BEAMS)
		return (mat_by_pattern_beams(relative_pos,
				sp_pattern_mats(BEAMS, sp), sp->radius * 2));
	return (sp->material);
}

/**
 * @returns The material at this position of the plane
 */
t_material	mat_at_hit_on_plane(t_vec4 *hit_pos, t_plane *pl)
{
	const t_vec4	relative_pos = transformed_vec(*hit_pos, pl->inverse);

	if (pl->image)
		return (mat_by_texture_plane(relative_pos, pl));
	else if (pl->pattern == SOLID)
		return (pl->material);
	else if (pl->pattern == CHECKERBOARD)
		return (mat_by_pattern_checkerboard(relative_pos,
				pl_pattern_mats(CHECKERBOARD, plane), PLANE, -1));
	else if (plane->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				pl_pattern_mats(CANDY, pl)));
	else if (pl->pattern == CIRCUS)
		return (mat_by_pattern_circus(relative_pos,
				pl_pattern_mats(CIRCUS, pl)));
	else if (pl->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				pl_pattern_mats(LINES, pl)));
	else if (pl->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				pl_pattern_mats(ANGEL, pl)));
	else if (pl->pattern == BEAMS)
		return (mat_by_pattern_beams(relative_pos,
				pl_pattern_mats(BEAMS, plane), -1));
	return (plane->material);
}

/**
 * @returns The material at this position of the cylinder
 */
t_material	mat_at_hit_on_cylinder(t_vec4 *hit_pos, t_cylinder *cyl)
{
	const t_vec4	relative_pos = transformed_vec(*hit_pos, cyl->inverse);

	if (cyl->image)
		return (mat_by_texture_cylinder(relative_pos, cyl));
	else if (cyl->pattern == SOLID)
		return (cyl->material);
	else if (cyl->pattern == CHECKERBOARD)
		return (mat_by_pattern_checkerboard(relative_pos,
				cy_pattern_mats(CHECKERBOARD, cyl), CYLINDER, cyl->height));
	else if (cyl->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				cy_pattern_mats(BEAMS, cyl)));
	else if (cyl->pattern == CIRCUS)
		return (mat_by_pattern_circus(relative_pos,
				cy_pattern_mats(CIRCUS, cyl)));
	else if (cyl->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				cy_pattern_mats(LINES, cyl)));
	else if (cyl->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				cy_pattern_mats(ANGEL, cyl)));
	else if (cyl->pattern == BEAMS)
		return (mat_by_pattern_beams(relative_pos,
				cy_pattern_mats(BEAMS, cyl), cyl->height));
	return (cyl->material);
}

/**
 * @returns The material at this position of the triangle
 *
 * (Some patterns are absent because we consider them invalid for triangles,
 *  those get rejected during parsing)
 */
t_material	mat_at_hit_on_triangle(t_vec4 *hit_pos, t_triangle *tr)
{
	const t_vec4	relative_pos = *hit_pos;

	if (tr->pattern == SOLID)
		return (tr->material);
	else if (tr->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				tr_pattern_mats(BEAMS, tr)));
	else if (tr->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				tr_pattern_mats(LINES, tr)));
	else if (tr->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				tr_pattern_mats(ANGEL, tr)));
	return (tr->material);
}

/**
 * @returns The material at this position of the triangle
 *
 * (Some patterns are absent because we consider them invalid for triangles,
 *  those get rejected during parsing)
 */
t_material	material_at_hit_on_triangle(t_vec4 *hit_pos, t_triangle *triangle)
{
	const t_vec4	relative_pos = *hit_pos;

	if (triangle->pattern == SOLID)
		return (triangle->material);
	else if (triangle->pattern == CANDY)
		return (mat_by_pattern_candy(relative_pos,
				tr_pattern_mats(BEAMS, triangle)));
	else if (triangle->pattern == LINES)
		return (mat_by_pattern_lines(relative_pos,
				tr_pattern_mats(LINES, triangle)));
	else if (triangle->pattern == ANGEL)
		return (mat_by_pattern_angel(relative_pos,
				tr_pattern_mats(ANGEL, triangle)));
	return (triangle->material);
}
