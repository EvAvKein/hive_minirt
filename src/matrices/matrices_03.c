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

/**
 * @returns	Identity 4x4 matrix (elem = 1 when row == col)
 */
t_m4x4	identity_m4x4(void)
{
	static t_m4x4 const	identity = (t_m4x4){
		._[0][0] = 1, ._[1][1] = 1, ._[2][2] = 1, ._[3][3] = 1};

	return (identity);
}

/**
 * @returns	Transpose matrix of m4x4 (first row becomes first column etc.)
 */
t_m4x4	transpose_m4x4(t_m4x4 const *m4x4)
{
	t_m4x4	transpose;
	size_t	i;

	i = -1;
	while (++i < 16)
		transpose._[i / 4][i % 4] = m4x4->_[i % 4][i / 4];
	return (transpose);
}

/**
 * @returns	Cofactor at row and col, which is the determinant of the submatrix
 *			in which the row and column have been removed, signed based on if
 *			the sum of the row and column indices is odd or even
 */
t_flt	cofactor_m4x4(t_m4x4 const *m4x4, size_t row, size_t col)
{
	t_m3x3	sub;

	sub = sub_m4x4(m4x4, row, col);
	if ((row + col) % 2 != 0)
		return (-det_m3x3(&sub));
	return (det_m3x3(&sub));
}

/**
 * @returns	The inverse matrix of m4x4 when m4x4 is invertible, a zero matrix if
 *			m4x4 is not invertible
 */
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
