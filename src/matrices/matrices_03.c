/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:57:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/04 10:49:22 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_m4x4	identity_m4x4(void)
{
	static t_m4x4 const	identity = (t_m4x4){
		._[0][0] = 1, ._[1][1] = 1, ._[2][2] = 1, ._[3][3] = 1};

	return (identity);
}

t_m4x4	transpose_m4x4(t_m4x4 const *m4x4)
{
	t_m4x4	transpose;
	size_t	i;

	i = -1;
	while (++i < 16)
		transpose._[i / 4][i % 4] = m4x4->_[i % 4][i / 4];
	return (transpose);
}

t_flt	cofactor_m4x4(t_m4x4 const *m4x4, size_t row, size_t col)
{
	t_m3x3	sub;

	sub = sub_m4x4(m4x4, row, col);
	if ((row + col) % 2 != 0)
		return (-det_m3x3(&sub));
	return (det_m3x3(&sub));
}

t_m4x4	inverse_m4x4(t_m4x4 const *m4x4)
{
	t_m4x4	inverse;
	t_flt	det;
	size_t	i;

	det = det_m4x4(m4x4);
	if (det == 0)
		return ((t_m4x4){0});
	i = -1;
	while (++i < 16)
		inverse._[i % 4][i / 4] = cofactor_m4x4(m4x4, i / 4, i % 4) / det;
	return (inverse);
}
