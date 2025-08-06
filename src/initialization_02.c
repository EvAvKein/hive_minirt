/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:11:29 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/05 18:45:43 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_lights(t_light *light)
{
	t_ambient_light *const	amb = g_data.elems.ambient_light;

	amb->color.flt = color_8bit_to_flt(amb->color.bit);
	while (light)
	{
		light->transform = identity_m4x4();
		light->color.flt = color_8bit_to_flt(light->color.bit);
		light = light->next;
	}
}

void	init_spheres(t_sphere *sp)
{
	while (sp)
	{
		init_sphere_transform(sp);
		sp->material = default_material();
		sp->color.flt = color_8bit_to_flt(sp->color.bit);
		sp->material.color = point(sp->color.flt.r,
				sp->color.flt.g, sp->color.flt.b);
		sp = sp->next;
	}
}

void	init_planes(t_plane *pl)
{
	while (pl)
	{
		init_plane_transform(pl);
		pl->material = default_material();
		pl->color.flt = color_8bit_to_flt(pl->color.bit);
		pl->material.color = point(pl->color.flt.r,
				pl->color.flt.g, pl->color.flt.b);
		pl = pl->next;
	}
}

void	init_cylinders(t_cylinder *cyl)
{
	while (cyl)
	{
		init_cylinder_transform(cyl);
		cyl->material = default_material();
		cyl->color.flt = color_8bit_to_flt(cyl->color.bit);
		cyl->material.color = point(cyl->color.flt.r,
				cyl->color.flt.g, cyl->color.flt.b);
		cyl = cyl->next;
	}
}

void	init_triangles(t_triangle *tr)
{
	while (tr)
	{
		tr->material = default_material();
		tr->color.flt = color_8bit_to_flt(tr->color.bit);
		tr->material.color = point(tr->color.flt.r,
				tr->color.flt.g, tr->color.flt.b);
		tr = tr->next;
	}
}
