/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc_linked_lists.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/22 09:35:07 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *
 * Deallocate all the lights in the provided linked list from the heap.
 *
 * @param light	First node in light linked list
 * 
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
 *
 * Deallocate all the spheres in the provided linked list from the heap.
 * 
 * @param sphere	First node in sphere linked list
 *
 */
void	dealloc_spheres(t_sphere *sphere)
{
	t_sphere	*next;

	while (sphere)
	{
		next = sphere->next;
		free(sphere);
		sphere = next;
	}
}

/**
 *
 * Deallocate all the planes in the provided linked list from the heap.
 * 
 * @param plane	First node in plane linked list
 *
 */
void	dealloc_planes(t_plane *plane)
{
	t_plane	*next;

	while (plane)
	{
		next = plane->next;
		free(plane);
		plane = next;
	}
}

/**
 *
 * Deallocate all the cylinders in the provided linked list from the heap.
 * 
 * @param cylinder	First node in cylinder linked list
 *
 */
void	dealloc_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*next;

	while (cylinder)
	{
		next = cylinder->next;
		free(cylinder);
		cylinder = next;
	}
}
