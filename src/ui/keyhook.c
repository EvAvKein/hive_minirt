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

static int	handle_rotation(t_data *data, struct mlx_key_data key_data,
				t_flt move_speed, int *move_count)
{
	if (mlx_is_key_down(g_data.mlx, KEYBIND_RREV))
		move_speed = -move_speed;
	if (key_data.key == KEYBIND_RX && ++move_count)
		data->elems.camera->orientation.x += move_speed; // TODO:
	else if (key_data.key == KEYBIND_RY && ++move_count)
		data->elems.camera->orientation.y += move_speed; // TODO:
	else if (key_data.key == KEYBIND_RZ && ++move_count)
		data->elems.camera->orientation.z += move_speed; // TODO:
	return (*move_count);
}

static int	handle_movement(t_data *data, struct mlx_key_data key_data,
				t_flt move_speed, int *move_count)
{
	if (key_data.key == KEYBIND_MUP && ++move_count)
		data->elems.camera->pos.y += move_speed; // TODO:?
	else if (key_data.key == KEYBIND_MDOWN && ++move_count)
		data->elems.camera->pos.y -= move_speed; // TODO:?
	else if (key_data.key == KEYBIND_MRIGHT && ++move_count)
		data->elems.camera->pos.x += move_speed; // TODO:?
	else if (key_data.key == KEYBIND_MLEFT && ++move_count)
		data->elems.camera->pos.x -= move_speed; // TODO:?
	else if (key_data.key == KEYBIND_MFORWARD && ++move_count)
		data->elems.camera->pos.z += move_speed; // TODO:?
	else if (key_data.key == KEYBIND_MBACKWARD && ++move_count)
		data->elems.camera->pos.z -= move_speed; // TODO:?
	return (*move_count);
}

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
		print_vec(g_data.elems.camera->pos);
		write(STDIN_FILENO, "orientation: ", 14);
		print_vec(g_data.elems.camera->orientation);
	}
	data->pause = false;
}
