/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:11:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/13 17:28:32 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_camera(t_vec4 move_vec);
static void	handle_camera_rotation_input(void);
static void	handle_camera_translation_input(void);

/**
 * Function checks for user input and resize events every frame, handles those
 * events, resizes the image buffer when necessary and triggers a rerender for
 * the rendering threads.
 */
void	every_frame(void *param)
{
	(void)param;
	if (!mlx_is_key_down(dat()->mlx, KEYBIND_OBJ))
	{
		handle_camera_rotation_input();
		handle_camera_translation_input();
		handle_camera_fov_input();
	}
	else
	{
		handle_object_rotation_input();
		handle_object_translation_input();
	}
	if (dat()->resized)
	{
		dat()->resized = false;
		dat()->pause_threads = true;
		while (dat()->active_threads != 0)
			usleep(TICK * 10);
		mlx_resize_image(dat()->img, dat()->mlx->width, dat()->mlx->height);
		setup_pixel_grid(dat()->img->width, dat()->img->height);
		printf("Image dimensions:	width: %u	height: %u\n",
			dat()->img->width, dat()->img->height);
		reset_rendering_threads();
	}
}

/**
 * @returns	2D vector containing scalars for rotation deltas
 */
t_vec2	get_rotation_input_axes(void)
{
	t_vec2	axes;
	t_flt	rotation_speed;

	axes = (t_vec2){};
	rotation_speed = ROTATION_BASE;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_FAST))
		rotation_speed *= ROTATION_MULT;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_RX))
		axes.x = rotation_speed;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_RRX))
		axes.x = -rotation_speed;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_RY))
		axes.y = rotation_speed;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_RRY))
		axes.y = -rotation_speed;
	return (axes);
}

/**
 * Calculates the current pitch and yaw of the camera and updates them based on
 * the values in axes. The x rotation (pitch) is limited to -pi/2 -> pi/2.
 * Function also notifies threads of the update.
 */
static void	handle_camera_rotation_input(void)
{
	t_camera *const	cam = dat()->elems.camera;
	t_vec2			axes;
	t_vec2			angles;

	axes = get_rotation_input_axes();
	if (flts_are_equal(axes.x, 0) && flts_are_equal(axes.y, 0))
		return ;
	angles = cam_pitch_and_yaw(dat()->elems.camera);
	if ((angles.x + axes.x < M_PI_2) && (angles.x + axes.x > -M_PI_2))
		angles.x += axes.x;
	else if (flts_are_equal(axes.y, 0))
		return ;
	dat()->pause_threads = true;
	angles.y += axes.y;
	cam->transform = x_rotation_m4x4(-angles.x);
	cam->transform = mult_m4x4(y_rotation_m4x4(angles.y), cam->transform);
	cam->transform = mult_m4x4(translation_m4x4(cam->pos), cam->transform);
	cam->inverse = inverse_m4x4(cam->transform);
	cam->orientation = transformed_vec(vector(0, 0, 1), cam->transform);
	ft_putstr_fd("Camera orientation:	", STDOUT_FILENO);
	print_vec(cam->orientation);
	reset_rendering_threads();
}

/**
 * Cheks for movement keypresses and activates camera moving function when
 * necessary.
 */
static void	handle_camera_translation_input(void)
{
	t_camera *const	cam = dat()->elems.camera;
	t_vec4 const	camera_right = unit_vec(cross(vector(0, 1, 0),
				cam->orientation));
	t_vec4 const	camera_up = unit_vec(cross(cam->orientation, camera_right));
	t_vec4			move_vec;

	move_vec = (t_vec4){0};
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MUP))
		move_vec = vec_sum(move_vec, camera_up);
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MDOWN))
		move_vec = vec_sum(move_vec, opposite_vec(camera_up));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MRIGHT))
		move_vec = vec_sum(move_vec, camera_right);
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MLEFT))
		move_vec = vec_sum(move_vec, opposite_vec(camera_right));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MFORWARD))
		move_vec = vec_sum(move_vec, cam->orientation);
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MBACKWARD))
		move_vec = vec_sum(move_vec, opposite_vec(cam->orientation));
	move_vec = scaled_vec(unit_vec(move_vec), MOVEMENT_BASE);
	if (mlx_is_key_down(dat()->mlx, KEYBIND_FAST))
		move_vec = scaled_vec(move_vec, MOVEMENT_MULT);
	if (!vecs_are_equal(move_vec, vector(0, 0, 0)))
		move_camera(move_vec);
}

/**
 * Updates camera's position.
 *
 * @param move_vec	Translation vector that is added to the camera's position
 */
static void	move_camera(t_vec4 move_vec)
{
	t_data *const	data = dat();

	data->pause_threads = true;
	data->elems.camera->pos = vec_sum(data->elems.camera->pos, move_vec);
	init_camera_transform(data->elems.camera);
	ft_putstr_fd("Camera position:	", STDOUT_FILENO);
	print_vec(data->elems.camera->pos);
	reset_rendering_threads();
}
