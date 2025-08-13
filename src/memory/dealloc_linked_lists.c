/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc_linked_lists.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/05 15:11:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Deallocate all the lights in the provided linked list from the heap.
 *
 * @param light	First node in light linked list
 */
void	dealloc_lights(t_light *light)
{
	t_light	*next;

	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
}

/**
 * Deallocate all spheres in the provided linked list from the heap,
 * also freeing any associated MLX assets.
 * 
 * @param sphere	First node in sphere linked list
 */
void	dealloc_spheres(t_sphere *sphere)
{
	t_sphere	*next;

	while (sphere)
	{
		if (sphere->texture)
			mlx_delete_texture(sphere->texture);
		if (sphere->image)
			mlx_delete_image(dat()->mlx, sphere->image);
		next = sphere->next;
		free(sphere);
		sphere = next;
	}
}

/**
 * Deallocate all the planes in the provided linked list from the heap,
 * also freeing any associated MLX assets.
 * 
 * @param plane	First node in plane linked list
 */
void	dealloc_planes(t_plane *plane)
{
	t_plane	*next;

	while (plane)
	{
		if (plane->texture)
			mlx_delete_texture(plane->texture);
		if (plane->image)
			mlx_delete_image(dat()->mlx, plane->image);
		next = plane->next;
		free(plane);
		plane = next;
	}
}

/**
 * Deallocate all the cylinders in the provided linked list from the heap,
 * also freeing any associated MLX assets.
 * 
 * @param cylinder	First node in cylinder linked list
 */
void	dealloc_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*next;

	while (cylinder)
	{
		if (cylinder->texture)
			mlx_delete_texture(cylinder->texture);
		if (cylinder->image)
			mlx_delete_image(dat()->mlx, cylinder->image);
		next = cylinder->next;
		free(cylinder);
		cylinder = next;
	}
}

/**
 * Deallocate all the triangles in the provided linked list from the heap.
 *
 * @param triangle	First node in triangle linked list
 */
void	dealloc_triangles(t_triangle *triangle)
{
	t_triangle	*next;

	while (triangle)
	{
		next = triangle->next;
		free(triangle);
		triangle = next;
	}
}
