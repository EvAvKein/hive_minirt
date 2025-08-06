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

void	wait_for_threads_and_restart(void)
{
	while (g_data.active_threads != 0)
		usleep(TICK);
	g_data.jobs_available = THREADS;
	g_data.active_threads = 0;
	g_data.pause = false;
}

void	update_camera_rotation(t_flt amount, t_axis axis)
{
	t_camera *const	cam = g_data.elems.camera;
	t_vec2			angles;
	t_vec4			new_orientation;

	g_data.pause = true;
	angles = cam_pitch_and_yaw(g_data.elems.camera);
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
	wait_for_threads_and_restart();
}

void	rotation_hook(void *param)
{
	t_flt	rotation_speed;

	(void)param;
	rotation_speed = ROTATION_BASE;
	if (mlx_is_key_down(g_data.mlx, KEYBIND_FAST))
		rotation_speed *= ROTATION_MULT;
	if (mlx_is_key_down(g_data.mlx, KEYBIND_RX))
		update_camera_rotation(rotation_speed, X);
	if (mlx_is_key_down(g_data.mlx, KEYBIND_RRX))
		update_camera_rotation(-rotation_speed, X);
	else if (mlx_is_key_down(g_data.mlx, KEYBIND_RY))
		update_camera_rotation(rotation_speed, Y);
	else if (mlx_is_key_down(g_data.mlx, KEYBIND_RRY))
		update_camera_rotation(-rotation_speed, Y);
}

/**
 * TODO: Write documentation
 */
void	esc_and_screenshot_hook(mlx_key_data_t key_data, void *param)
{
	t_data *const	data = param;

	(void)key_data;
	if (mlx_is_key_down(data->mlx, KEYBIND_QUIT))
	{
		data->stop = true;
		while (data->active_threads > 0)
			usleep(500);
		mlx_terminate(g_data.mlx);
		free_data();
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(data->mlx, KEYBIND_SAVE))
	{
		image_to_file("miniRT.bmp");
		return ;
	}
}

void	move_camera(t_vec4 move_vec)
{
	g_data.pause = true;
	g_data.elems.camera->pos = vec_sum(g_data.elems.camera->pos, move_vec);
	init_camera_transform(g_data.elems.camera);
	wait_for_threads_and_restart();
}

void	movement_hook(void *param)
{
	t_camera *const	cam = ((t_data *)param)->elems.camera;
	t_vec4 const	camera_right = unit_vec(cross(vector(0, 1, 0),
											cam->orientation));
	t_vec4 const	camera_up = unit_vec(cross(cam->orientation,
										camera_right));
	t_vec4			move_vec;

	move_vec = (t_vec4){0};
	if (mlx_is_key_down(g_data.mlx, KEYBIND_MUP))
		move_vec = vec_sum(move_vec, camera_up);
	if (mlx_is_key_down(g_data.mlx, KEYBIND_MDOWN))
		move_vec = vec_sum(move_vec, opposite_vec(camera_up));
	if (mlx_is_key_down(g_data.mlx, KEYBIND_MRIGHT))
		move_vec = vec_sum(move_vec, camera_right);
	if (mlx_is_key_down(g_data.mlx, KEYBIND_MLEFT))
		move_vec = vec_sum(move_vec, opposite_vec(camera_right));
	if (mlx_is_key_down(g_data.mlx, KEYBIND_MFORWARD))
		move_vec = vec_sum(move_vec, cam->orientation);
	if (mlx_is_key_down(g_data.mlx, KEYBIND_MBACKWARD))
		move_vec = vec_sum(move_vec, opposite_vec(cam->orientation));
	move_vec = unit_vec(move_vec);
	if (mlx_is_key_down(g_data.mlx, KEYBIND_FAST))
		move_vec = scaled_vec(move_vec, MOVEMENT_MULT);
	if (!vecs_are_equal(move_vec, vector(0, 0, 0)))
		move_camera(move_vec);
}
