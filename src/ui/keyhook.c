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

typedef enum e_axis
{
	X = 0,
	Y,
	Z
}	t_axis;

void	update_camera_rotation(t_flt amount, t_axis axis)
{
	t_camera *const	cam = g_data.elems.camera;
	t_vec2			angles;
	t_vec4			new_orientation;

	angles = cam_pitch_and_yaw(g_data.elems.camera);
	printf("Camera initial x angle:	%f\n", DEGREES_PER_RADIAN * angles.x);
	printf("Camera initial y angle:	%f\n", DEGREES_PER_RADIAN * angles.y);
	if (axis == X)
		angles.x += amount;
	else if (axis == Y)
		angles.y += amount;
	new_orientation = (t_vec4){.z = 1};
	cam->transform = x_rotation_m4x4(-angles.x);
	cam->transform = mult_m4x4(y_rotation_m4x4(angles.y), cam->transform);
	cam->transform = mult_m4x4(translation_m4x4(cam->pos), cam->transform);
	cam->inverse = inverse_m4x4(cam->transform);
	cam->orientation = transformed_vec(new_orientation, cam->transform);
}

static int	handle_rotation(struct mlx_key_data key_data,
				t_flt move_speed, size_t *move_count)
{
	if (mlx_is_key_down(g_data.mlx, KEYBIND_RREV))
		move_speed = -move_speed;
	if (key_data.key == KEYBIND_RX && ++move_count)
		update_camera_rotation(move_speed, X);
	else if (key_data.key == KEYBIND_RY && ++move_count)
		update_camera_rotation(move_speed, Y);
	return (*move_count);
}

static int	handle_movement(struct mlx_key_data key_data,
				t_flt move_speed, size_t *move_count)
{
	if (key_data.key == KEYBIND_MUP && ++move_count)
		g_data.elems.camera->pos.y += move_speed;
	else if (key_data.key == KEYBIND_MDOWN && ++move_count)
		g_data.elems.camera->pos.y -= move_speed;
	else if (key_data.key == KEYBIND_MRIGHT && ++move_count)
		g_data.elems.camera->pos.x += move_speed;
	else if (key_data.key == KEYBIND_MLEFT && ++move_count)
		g_data.elems.camera->pos.x -= move_speed;
	else if (key_data.key == KEYBIND_MFORWARD && ++move_count)
		g_data.elems.camera->pos.z += move_speed;
	else if (key_data.key == KEYBIND_MBACKWARD && ++move_count)
		g_data.elems.camera->pos.z -= move_speed;
	init_camera_transform(g_data.elems.camera);
	return (*move_count);
}

/**
 * TODO: Write documentation
 */
void	keyhook(mlx_key_data_t key_data, void *param)
{
	t_data *const	data = param;
	t_flt			move_speed;
	size_t			move_count;
	t_flt			rotation_speed;
	size_t			rotation_count;

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
	{
		image_to_file("miniRT.bmp");
		return ;
	}
	move_speed = MOVEMENT_BASE;
	rotation_speed = ROTATION_BASE;
	if (mlx_is_key_down(data->mlx, KEYBIND_FAST))
	{
		move_speed *= MOVEMENT_MULT;
		rotation_speed *= MOVEMENT_MULT;
	}
	data->pause = true;
	move_count = 0;
	rotation_count = 0;
	if (handle_movement(key_data, move_speed, &move_count)
		|| handle_rotation(key_data, rotation_speed, &rotation_count))
	{
		ft_putstr_fd("Camera position:	", STDOUT_FILENO);
		print_vec(g_data.elems.camera->pos);
		ft_putstr_fd("Camera orientation:	", STDOUT_FILENO);
		print_vec(g_data.elems.camera->orientation);
	}
	while (data->active_threads != 0)
		usleep(TICK);
	data->jobs_available = THREADS;
	data->active_threads = 0;
	data->pause = false;
}
