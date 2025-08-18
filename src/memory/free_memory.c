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

	if (dat()->elems.ambient_light
		&& dat()->elems.ambient_light->sky_texture)
		mlx_delete_texture(dat()->elems.ambient_light->sky_texture);
	free(dat()->elems.ambient_light);
	free(dat()->elems.camera);
	dealloc_lights(dat()->elems.lights);
	dealloc_spheres(dat()->elems.spheres);
	dealloc_planes(dat()->elems.planes);
	dealloc_cylinders(dat()->elems.cylinders);
	dealloc_triangles(dat()->elems.triangles);
	i = -1;
	while (++i < THREADS)
		pthread_join(dat()->threads[i], NULL);
	pthread_mutex_destroy(&dat()->lock);
	return (true);
}
