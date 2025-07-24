/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:51:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/24 10:39:06 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param x	Float to be used as the x axis of the vector
 * @param y	Float to be used as the y axis of the vector
 * @param z	Float to be used as the z axis of the vector
 *
 * @returns	New t_vec4 struct with the given floats as dimensions, w set to 0
 */
t_vec4	vector(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.x = x,
		.y = y,
		.z = z,
		.w = 0});
}

/**
 * @param x	Float to be used as the x axis of the position
 * @param y	Float to be used as the y axis of the position
 * @param z	Float to be used as the z axis of the position
 *
 * @returns	New t_vec4 struct with the given floats as dimensions, w set to 1
 */
t_vec4	point(t_flt x, t_flt y, t_flt z)
{
	return ((t_vec4){
		.x = x,
		.y = y,
		.z = z,
		.w = 1});
}

void	print_vec(t_vec4 vec)
{
	printf("Vec:	x = %f	y = %f	z = %f	w = %f\n",
		vec.x, vec.y, vec.z, vec.w);
}
