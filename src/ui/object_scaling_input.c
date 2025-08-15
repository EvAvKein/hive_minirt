/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_scaling_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:27:55 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/15 13:28:14 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_object_scaling_input(void)
{
	t_obj	ob;
	t_vec4	scaling_factors;
	t_flt	scalar;

	scaling_factors = point(1, 1, 1);
	scalar = SCALE_DELTA;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_FAST))
		scalar *= SCALE_MULT;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_SCALE_INC))
		scaling_factors = scaled_vec(scaling_factors, scalar);
	if (mlx_is_key_down(dat()->mlx, KEYBIND_SCALE_DEC))
		scaling_factors = scaled_vec(scaling_factors, 1 / scalar);
	if (vecs_are_equal(scaling_factors, point(1, 1, 1)))
		return ;
	dat()->pause_threads = true;
	ob = match_selected_object();
	ob.transf = mult_m4x4(translation_m4x4(opposite_vec(ob.pos)), ob.transf);
	ob.transf = mult_m4x4(scaling_m4x4(scaling_factors), ob.transf);
	ob.transf = mult_m4x4(translation_m4x4(ob.pos), ob.transf);
	ob.inv = inverse_m4x4(ob.transf);
	update_selected_object(ob);
	reset_rendering_threads();
}
