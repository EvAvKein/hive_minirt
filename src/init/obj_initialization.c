/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:11:29 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 17:15:48 by ekeinan          ###   ########.fr       */
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
		sp->material = default_material();
		sp->material.color = point(sp->color.r, sp->color.g, sp->color.b);
		sp = sp->next;
	}
}

void	init_planes(t_plane *pl)
{
	while (pl)
	{
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
		tr->material = default_material();
		tr->material.color = point(tr->color.r, tr->color.g, tr->color.b);
		tr = tr->next;
	}
}
