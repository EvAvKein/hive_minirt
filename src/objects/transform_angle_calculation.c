/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_angle_calculation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:25:15 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/23 16:26:18 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculates pitch and yaw rotations for camera.
 *
 * @param cam	Camera struct pointer
 *
 * @returns	Float array containing the pitch and yaw angles
 */
t_vec2	cam_pitch_and_yaw(t_camera *cam)
{
	t_vec2	angles;
	t_vec4	h;

	angles = (t_vec2){};
	angles.x = atan2(cam->orientation.y, vec_len(point(cam->orientation.x,
					0, cam->orientation.z)));
	h = unit_vec(vector(cam->orientation.x, 0, cam->orientation.z));
	angles.y = atan2(h.x, h.z);
	return (angles);
}

/**
 * Calculates pitch and yaw rotations for a plane.
 *
 * @param cam	Plane struct
 *
 * @returns	Float array containing the pitch and yaw angles
 */
t_vec2	plane_pitch_and_yaw(t_plane pl)
{
	t_vec2	angles;
	t_vec4	h;

	angles = (t_vec2){};
	h = pl.orientation;
	angles.x = atan2(vec_len(point(h.x, 0, h.z)), h.y);
	h = unit_vec(vector(pl.orientation.x, 0, pl.orientation.z));
	angles.y = atan2(h.x, h.z);
	return (angles);
}
