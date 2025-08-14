/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_translation_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:38:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/13 16:23:44 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec4	get_translation_input_axes(void);

void	handle_object_translation_input(void)
{
	t_obj	ob;
	t_vec4	axes;

	axes = get_translation_input_axes();
	if (vecs_are_equal(axes, point(0, 0, 0)))
		return ;
	ob = match_selected_object();
	if (ob.type == UNKNOWN)
		return ;
	dat()->pause_threads = true;
	ob.pos = vec_sum(ob.pos, axes);
	ob.transf = mult_m4x4(translation_m4x4(axes), ob.transf);
	ob.inv = inverse_m4x4(ob.transf);
	update_selected_object(ob);
	ft_putstr_fd("Object position:	", STDOUT_FILENO);
	print_vec(ob.pos);
	reset_rendering_threads();
}

static t_vec4	get_translation_input_axes(void)
{
	t_vec4	axes;
	t_flt	translation_speed;

	translation_speed = MOVEMENT_BASE;
	axes = (t_vec4){0};
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MUP))
		axes = vec_sum(axes, point(0, 1, 0));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MDOWN))
		axes = vec_sum(axes, point(0, -1, 0));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MRIGHT))
		axes = vec_sum(axes, point(1, 0, 0));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MLEFT))
		axes = vec_sum(axes, point(-1, 0, 0));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MFORWARD))
		axes = vec_sum(axes, point(0, 0, 1));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_MBACKWARD))
		axes = vec_sum(axes, point(0, 0, -1));
	if (mlx_is_key_down(dat()->mlx, KEYBIND_FAST))
		translation_speed *= MOVEMENT_MULT;
	axes = scaled_vec(unit_vec(axes), translation_speed);
	axes.w = 1;
	return (axes);
}
