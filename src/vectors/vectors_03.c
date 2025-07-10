/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:07:33 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/10 11:12:40 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	vector(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.axis.x = x,
		.axis.y = y,
		.axis.z = z,
		.axis.w = 0});
}

t_vec4	position(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.axis.x = x,
		.axis.y = y,
		.axis.z = z,
		.axis.w = 1});
}
