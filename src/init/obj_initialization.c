/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:11:29 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/13 13:33:36 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_lights(t_light *light)
{
	while (light)
	{
		light->transform = identity_m4x4();
		light = light->next;
	}
}

void	init_spheres(t_sphere *sp)
{
	while (sp)
	{
		init_sphere_transform(sp);
		sp->initial_pos = sp->pos;
		sp->initial_orientation = vector(0, 1, 0);
		sp->orientation = sp->initial_orientation;
		sp->material = default_material();
		sp->material.color = point(sp->color.r, sp->color.g, sp->color.b);
		sp = sp->next;
	}
}

void	init_planes(t_plane *pl)
{
	while (pl)
	{
		pl->initial_pos = pl->pos;
		pl->initial_orientation = pl->orientation;
		init_plane_transform(pl);
		pl->material = default_material();
		pl->material.color = point(pl->color.r, pl->color.g, pl->color.b);
		pl = pl->next;
	}
}

void	init_cylinders(t_cylinder *cyl)
{
	while (cyl)
	{
		cyl->initial_pos = cyl->pos;
		cyl->initial_orientation = cyl->orientation;
		init_cylinder_transform(cyl);
		cyl->material = default_material();
		cyl->material.color = point(cyl->color.r, cyl->color.g, cyl->color.b);
		cyl = cyl->next;
	}
}

void	init_triangles(t_triangle *tr)
{
	while (tr)
	{
		tr->normal = unit_vec(cross(
					vec_sub(tr->pos2, (tr->pos1)),
					vec_sub(tr->pos3, (tr->pos1))));
		tr->material = default_material();
		tr->material.color = point(tr->color.r, tr->color.g, tr->color.b);
		tr = tr->next;
	}
}
