/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/06 13:57:13 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Free all heap-allocated memory in the program's data struct
 *
 * @returns `true`
 */
bool	free_data(void)
{
	size_t			i;

	if (g_data.elems.ambient_light
		&& g_data.elems.ambient_light->sky_texture)
		mlx_delete_texture(g_data.elems.ambient_light->sky_texture);
	free(g_data.elems.ambient_light);
	free(g_data.elems.camera);
	dealloc_lights(g_data.elems.lights);
	dealloc_spheres(g_data.elems.spheres);
	dealloc_planes(g_data.elems.planes);
	dealloc_cylinders(g_data.elems.cylinders);
	dealloc_triangles(g_data.elems.triangles);
	i = -1;
	while (++i < THREADS)
		pthread_join(g_data.threads[i], NULL);
	pthread_mutex_destroy(&g_data.lock);
	return (true);
}
