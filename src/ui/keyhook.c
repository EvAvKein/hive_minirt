/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:11:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/01 15:28:57 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * TODO: Write documentation
 */
void	keyhook(mlx_key_data_t key_data, void *param)
{
	t_data *const	data = param;
	t_flt			move_speed;
	int				move_count;

	if (mlx_is_key_down(data->mlx, KEYBIND_QUIT))
	{
		data->stop = true;
		while (data->active_threads > 0)
			usleep(500);
		mlx_terminate(g_data.mlx);
		free_data();
		exit(EXIT_SUCCESS);
	}
	if (key_data.key == KEYBIND_SAVE)
		image_to_file("miniRT.bmp");
	if (mlx_is_key_down(data->mlx, KEYBIND_FAST))
		move_speed = MOVEMENT_BASE * MOVEMENT_MULT;
	else
		move_speed = MOVEMENT_BASE;
	data->pause = true;
	if (handle_movement(data, key_data, move_speed, &move_count)
		|| handle_rotation(data, key_data, move_speed, &move_count))
	{
		write(STDIN_FILENO, "pos: ", 5);
		print_vec(get_data()->elems.camera->pos);
		write(STDIN_FILENO, "orientation: ", 14);
		print_vec(get_data()->elems.camera->orientation);
	}
	data->pause = false;
}
