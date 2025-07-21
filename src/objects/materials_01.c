/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:42:27 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/15 15:33:49 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	material(t_flt amb, t_flt diff, t_flt spec, t_flt shiny)
{
	return ((t_material){
		.ambient = amb,
		.diffuse = diff,
		.specular = spec,
		.shininess = shiny
	});
}

t_material	default_material(void)
{
	return ((t_material){
		.color = (t_vec4){.x = .8, .y = .8, .z = .8, .w = .8},
		.ambient = 0.2,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200
	});
}
