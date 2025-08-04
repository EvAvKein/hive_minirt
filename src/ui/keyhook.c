/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:11:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/11 10:21:43 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * TODO: Write documentation
 */
void	keyhook(mlx_key_data_t key_data, void *param)
{
	t_data *const	data = param;

	if (key_data.key == MLX_KEY_ESCAPE)
	{
		data->stop = true;
		while (data->active_threads > 0)
			usleep(500);
		mlx_terminate(g_data.mlx);
		free_data();
		exit(EXIT_SUCCESS);
	}
	if (key_data.modifier == MLX_CONTROL && key_data.key == MLX_KEY_S)
		image_to_file("miniRT.bmp");
}
