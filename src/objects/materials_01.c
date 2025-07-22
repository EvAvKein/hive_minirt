/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:42:27 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 11:14:33 by jvarila          ###   ########.fr       */
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
 * @reutrns	Material struct with colors set to match the float parameters
 */
t_material	material(t_flt r, t_flt g, t_flt b)
{
	t_material	mat;

	mat = default_material();
	mat.color = point(r, g, b);
	return (mat);
}

/**
 * @returns	Default material struct
 */
t_material	default_material(void)
{
	return ((t_material){
		.color = (t_vec4){.x = .7, .y = .7, .z = .7, .w = .7},
		.ambient = 0.2,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200
	});
}
