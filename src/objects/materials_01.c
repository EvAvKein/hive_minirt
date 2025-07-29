/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:42:27 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/27 16:16:41 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Convenience function to create material structs with.
 *
 * @param r	Red component of color (float)
 * @param g	Green component of color (float)
 * @param b	Blue component of color (float)
 *
 * @returns	Material struct with colors set to match the float parameters
 */
t_material	material(t_flt r, t_flt g, t_flt b)
{
	t_material	mat;

	mat = default_material();
	mat.color = point(r, g, b);
	return (mat);
}

/**
 * @param pattern_name	Pattern for which to return the corresponding material
 *
 * @returns The material of the pattern named by the `pattern_name` param
 */
t_material	mat_of_pattern(t_pattern pattern_name)
{
	static const t_material	default_mats[] = {
	[SOLID] = {.color = (t_vec4){.x = 0, .y = 0, .z = 0, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 100},
	[CHECKERBOARD] = {.color = (t_vec4){.x = 0, .y = 0, .z = 0, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 100},
	[CANDY] = {.color = (t_vec4){.x = 1, .y = 0.6, .z = 0.65, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 100},
	[CIRCUS] = {.color = (t_vec4){.x = 1, .y = 0, .z = 0, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 250},
	[LINES] = {.color = (t_vec4){.x = 0.72, .y = 0.65, .z = 0.98, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 100},
	[ANGEL] = {.color = (t_vec4){.x = 0.83, .y = 0.69, .z = 0.22, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 500},
	[BEAMS] = {.color = (t_vec4){.x = 0.9, .y = 0.9, .z = 0.1, .w = 1},
		.ambient = 0.2, .diffuse = 1, .specular = 1, .shininess = 100}
	};

	return (default_mats[pattern_name]);
}

/**
 * @returns	Default material struct
 */
t_material	default_material(void)
{
	return (mat_of_pattern(SOLID));
}

/**
 * @param pattern_name	Pattern for which to return the corresponding material
 * 						(with its color replaced based on the `color` param)
 *
 * @param color			An 8-bit color to convert and set to returned material
 *
 * @returns				The material of the provided pattern,
 * 						with its color set to the converted provided color
 */
t_material	pattern_mat_with_color(t_pattern pattern_name, t_8bit_color color)
{
	t_material	mat;

	mat = mat_of_pattern(pattern_name);
	mat.color = color_8bit_to_vec4(color);
	return (mat);
}
