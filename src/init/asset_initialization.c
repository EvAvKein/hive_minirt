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

static bool	sky_asset_init_successful(void);
static bool	sphere_asset_init_successful(void);
static bool	plane_asset_init_successful(void);
static bool	cylinder_asset_init_successful(void);

bool	mlx_asset_init_successful(void)
{
	return (sky_asset_init_successful()
		&& sphere_asset_init_successful()
		&& plane_asset_init_successful()
		&& cylinder_asset_init_successful());
}

static bool	sky_asset_init_successful(void)
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

static bool	sphere_asset_init_successful(void)
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

static bool	plane_asset_init_successful(void)
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

static bool	cylinder_asset_init_successful(void)
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
