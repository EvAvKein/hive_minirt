/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:51:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/04 10:52:05 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_flt	dot_product(t_vec4 const *v1, t_vec4 const *v2)
{
	return (v1->_[0] * v2->_[0]
		 + v1->_[1] * v2->_[1]
		 + v1->_[2] * v2->_[2]);
}

void	print_vec(t_vec4 const *vec)
{
	printf("Vec:	x = %f	y = %f	z = %f	w = %f\n",
		vec->axis.x, vec->axis.y, vec->axis.z, vec->axis.w);
}
