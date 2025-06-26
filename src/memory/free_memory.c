/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/25 17:02:06 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * Free all heap-allocated memory in the program's data struct.
 * 
 */
void	free_data(void)
{
	t_data	*data;

	data = get_data();
	free(data->elems.ambient_light);
	free(data->elems.camera);
	dealloc_lights(data->elems.lights);
	dealloc_spheres(data->elems.spheres);
	dealloc_planes(data->elems.planes);
	dealloc_cylinders(data->elems.cylinders);
}
