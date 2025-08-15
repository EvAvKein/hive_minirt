/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:03:08 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 17:15:24 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	sky_asset_init_successful(void)
{
	if (dat()->elems.ambient_light->sky_texture)
	{
		dat()->sky_image = mlx_texture_to_image(dat()->mlx,
			dat()->elems.ambient_light->sky_texture);
		mlx_delete_texture(dat()->elems.ambient_light->sky_texture);
		dat()->elems.ambient_light->sky_texture = NULL;
		if (!dat()->sky_image)
			return (print_err("Failed to convert sky texture to MLX image"));
	}
	return (true);
}

bool	sphere_asset_init_successful(void)
{
	t_sphere	*sphere;

	sphere = dat()->elems.spheres;
	while (sphere)
	{
		if (!sphere->texture)
		{
			sphere = sphere->next;
			continue ;
		}
		sphere->image = mlx_texture_to_image(dat()->mlx, sphere->texture);
		mlx_delete_texture(sphere->texture);
		sphere->texture = NULL;
		if (!sphere->image)
			return (print_err("Failed to convert sphere texture to MLX image"));
		sphere = sphere->next;
	}
	return (true);
}

bool	plane_asset_init_successful(void)
{
	t_plane	*plane;

	plane = dat()->elems.planes;
	while (plane)
	{
		if (!plane->texture)
		{
			plane = plane->next;
			continue ;
		}
		plane->image = mlx_texture_to_image(dat()->mlx, plane->texture);
		mlx_delete_texture(plane->texture);
		plane->texture = NULL;
		if (!plane->image)
			return (print_err("Failed to convert plane texture to MLX image"));
		plane = plane->next;
	}
	return (true);
}

bool	cylinder_asset_init_successful(void)
{
	t_cylinder	*cylinder;

	cylinder = dat()->elems.cylinders;
	while (cylinder)
	{
		if (!cylinder->texture)
		{
			cylinder = cylinder->next;
			continue ;
		}
		cylinder->image = mlx_texture_to_image(dat()->mlx, cylinder->texture);
		mlx_delete_texture(cylinder->texture);
		cylinder->texture = NULL;
		if (!cylinder->image)
			return (print_err("Failed to convert cylinder texture"
					"to MLX image"));
		cylinder = cylinder->next;
	}
	return (true);
}

bool	cone_asset_init_successful(void)
{
	t_cone	*cone;

	cone = dat()->elems.cones;
	while (cone)
	{
		if (!cone->texture)
		{
			cone = cone->next;
			continue ;
		}
		cone->image = mlx_texture_to_image(dat()->mlx, cone->texture);
		mlx_delete_texture(cone->texture);
		cone->texture = NULL;
		if (!cone->image)
			return (print_err("Failed to convert cone texture"
					"to MLX image"));
		cone = cone->next;
	}
	return (true);
}
