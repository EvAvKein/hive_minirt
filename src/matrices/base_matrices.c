/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:57:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/24 10:49:36 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_flt	cofactor_m4x4(t_m4x4 m4x4, size_t row, size_t col);

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
 * @param m4x4_1	4 by 4 matrix to multiply m4x4_2 with
 * @param m4x4_2	4 by 4 matrix to get multiplied by m4x4_1
 *
 * @returns	Matrix that is the result of matrix multiplication between
 *			matrix_1 and matrix_2
 */
t_m4x4	mult_m4x4(t_m4x4 m4x4_1, t_m4x4 m4x4_2)
{
	int		m;
	t_m4x4	multiplied;

	m = -1;
	while (++m < 4)
	{
		multiplied._[m][0] = m4x4_1._[m][0] * m4x4_2._[0][0]
			+ m4x4_1._[m][1] * m4x4_2._[1][0]
			+ m4x4_1._[m][2] * m4x4_2._[2][0]
			+ m4x4_1._[m][3] * m4x4_2._[3][0];
		multiplied._[m][1] = m4x4_1._[m][0] * m4x4_2._[0][1]
			+ m4x4_1._[m][1] * m4x4_2._[1][1]
			+ m4x4_1._[m][2] * m4x4_2._[2][1]
			+ m4x4_1._[m][3] * m4x4_2._[3][1];
		multiplied._[m][2] = m4x4_1._[m][0] * m4x4_2._[0][2]
			+ m4x4_1._[m][1] * m4x4_2._[1][2]
			+ m4x4_1._[m][2] * m4x4_2._[2][2]
			+ m4x4_1._[m][3] * m4x4_2._[3][2];
		multiplied._[m][3] = m4x4_1._[m][0] * m4x4_2._[0][3]
			+ m4x4_1._[m][1] * m4x4_2._[1][3]
			+ m4x4_1._[m][2] * m4x4_2._[2][3]
			+ m4x4_1._[m][3] * m4x4_2._[3][3];
	}
	return (multiplied);
}

/**
 * @param m4x4	4 by 4 matrix to create transpose of
 *
 * @returns	Transpose matrix of m4x4 (first row becomes first column etc.)
 */
t_m4x4	transpose_m4x4(t_m4x4 m4x4)
{
	t_m4x4	transpose;
	size_t	i;

	i = -1;
	while (++i < 16)
		transpose._[i / 4][i % 4] = m4x4._[i % 4][i / 4];
	return (transpose);
}

/**
 * @param m4x4	4 by 4 matrix to create inverse matrix from
 *
 * @returns	The inverse matrix of m4x4 when m4x4 is invertible, a zero matrix if
 *			m4x4 is not invertible
 */
t_m4x4	inverse_m4x4(t_m4x4 m4x4)
{
	t_m4x4	inverse;
	t_flt	det;
	size_t	i;

	det = det_m4x4(m4x4);
	if (det == 0)
		return ((t_m4x4){});
	i = -1;
	while (++i < 16)
		inverse._[i % 4][i / 4] = cofactor_m4x4(m4x4, i / 4, i % 4) / det;
	return (inverse);
}

/**
 * @param m4x4	4 by 4 matrix from which to calculate cofactors
 * @param row	Row position of cofactor
 * @param col	Column position of cofactor
 *
 * @returns	Cofactor at row and col, which is the determinant of the submatrix
 *			in which the row and column have been removed, signed based on if
 *			the sum of the row and column indices is odd or even
 */
static t_flt	cofactor_m4x4(t_m4x4 m4x4, size_t row, size_t col)
{
	t_m3x3	sub;

	sub = sub_m4x4(m4x4, row, col);
	if ((row + col) % 2 != 0)
		return (-det_m3x3(sub));
	return (det_m3x3(sub));
}
