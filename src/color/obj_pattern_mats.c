/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_pattern_mats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:29:31 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/05 16:49:21 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern_mats	sp_pattern_mats(t_pattern pattern_name, t_sphere *sphere)
{
	return ((t_pattern_mats){
		.obj_mat = sphere->material,
		.pat_mat = pattern_mat_with_color(pattern_name, sphere->pattern_color)
	});
}

t_pattern_mats	pl_pattern_mats(t_pattern pattern_name, t_plane *plane)
{
	return ((t_pattern_mats){
		.obj_mat = plane->material,
		.pat_mat = pattern_mat_with_color(pattern_name, plane->pattern_color)
	});
}

t_pattern_mats	cy_pattern_mats(t_pattern pattern_name, t_cylinder *cylinder)
{
	return ((t_pattern_mats){
		.obj_mat = cylinder->material,
		.pat_mat = pattern_mat_with_color(pattern_name, cylinder->pattern_color)
	});
}

t_pattern_mats	tr_pattern_mats(t_pattern pattern_name, t_triangle *triangle)
{
	return ((t_pattern_mats){
		.obj_mat = triangle->material,
		.pat_mat = pattern_mat_with_color(pattern_name, triangle->pattern_color)
	});
}
