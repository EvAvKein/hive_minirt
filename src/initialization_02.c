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

static void	init_lights(t_light *light);
static void	init_spheres(t_sphere *sp);
static void	init_planes(t_plane *pl);
static void	init_cylinders(t_cylinder *cyl);

void	init_object_data(void)
{
	t_data *const	data = get_data();

	init_lights(data->elems.lights);
	init_spheres(data->elems.spheres);
	init_planes(data->elems.planes);
	init_cylinders(data->elems.cylinders);
	init_camera_transform(data->elems.camera);
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

static void	init_spheres(t_sphere *sp)
{
	while (sp)
	{
		init_sphere_transform(sp);
		sp->material = default_material();
		sp->color.flt = color_8bit_to_float(sp->color.bit);
		sp->material.color = point(sp->color.flt.r,
				sp->color.flt.g, sp->color.flt.b);
		sp = sp->next;
	}
}

static void	init_planes(t_plane *pl)
{
	while (pl)
	{
		init_plane_transform(pl);
		pl->material = default_material();
		pl->color.flt = color_8bit_to_float(pl->color.bit);
		pl->material.color = point(pl->color.flt.r,
				pl->color.flt.g, pl->color.flt.b);
		pl = pl->next;
	}
}

static void	init_cylinders(t_cylinder *cyl)
{
	while (cyl)
	{
		init_cylinder_transform(cyl);
		cyl->material = default_material();
		cyl->color.flt = color_8bit_to_float(cyl->color.bit);
		cyl->material.color = point(cyl->color.flt.r,
				cyl->color.flt.g, cyl->color.flt.b);
		cyl = cyl->next;
	}
}
