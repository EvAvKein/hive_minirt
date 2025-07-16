/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:11:29 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/16 10:32:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_spheres(t_sphere *sphere);
static void	init_lights(t_light *light);

void	init_object_data(void)
{
	t_data *const	data = get_data();

	init_lights(data->elems.lights);
	init_spheres(data->elems.spheres);
}

static void	init_lights(t_light *light)
{
	while (light)
	{
		light->transform = identity_m4x4();
		light->color.flt = color_8bit_to_float(light->color.bit);
		light = light->next;
	}
}

static void	init_spheres(t_sphere *sphere)
{
	while (sphere)
	{
		sphere->transform = translation_m4x4(sphere->pos);
		sphere->inverse = inverse_m4x4(sphere->transform);
		sphere->material = default_material();
		sphere->material.color = (t_vec4){
			.axis.x = 1,
			.axis.y = 0,
			.axis.z = 1,
			.axis.w = 1,
		};
		sphere = sphere->next;
	}
}
