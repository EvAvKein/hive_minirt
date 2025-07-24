/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_matrices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:57:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/24 10:51:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_m2x2	sub_m3x3(t_m3x3 m3x3, size_t row, size_t col);
static inline t_flt	det_m2x2(t_m2x2 m2x2);

/**
 * @param m3x3	3 by 3 matrix to construct submatrix from
 * @param row	Row to remove for the submatrix
 * @param col	Column to remove for the submatrix
 *
 * @returns	A submatrix of a 3x3 matrix, removes row and col from the original
 *			3x3 and packages the remaining elements into a 2x2 matrix, returns
 *			that matrix
 */
static inline t_m2x2	sub_m3x3(t_m3x3 m3x3, size_t row, size_t col)
{
	size_t	row_3x3;
	size_t	col_3x3;
	size_t	row_2x2;
	size_t	col_2x2;
	t_m2x2	new_m2x2;

	row_3x3 = -1;
	row_2x2 = 0;
	col_2x2 = 0;
	while (++row_3x3 < 3)
	{
		if (row_3x3 == row)
			continue ;
		col_3x3 = -1;
		while (++col_3x3 < 3)
		{
			if (col_3x3 == col)
				continue ;
			new_m2x2._[row_2x2][col_2x2++] = m3x3._[row_3x3][col_3x3];
		}
		++row_2x2;
		col_2x2 = 0;
	}
	return (new_m2x2);
}

/**
 * @param m4x4	4 by 4 matrix to construct submatrix from
 * @param row	Row to remove for the submatrix
 * @param col	Column to remove for the submatrix
 *
 * @returns	A submatrix of a 4x4 matrix, removes row and col from the original
 *			4x4 and packages the remaining elements into a 2x2 matrix, returns
 *			that matrix
 */
t_m3x3	sub_m4x4(t_m4x4 m4x4, size_t row, size_t col)
{
	size_t	row_3x3;
	size_t	col_3x3;
	size_t	row_2x2;
	size_t	col_2x2;
	t_m3x3	new_m3x3;

	row_3x3 = -1;
	row_2x2 = 0;
	col_2x2 = 0;
	while (++row_3x3 < 4)
	{
		if (row_3x3 == row)
			continue ;
		col_3x3 = -1;
		while (++col_3x3 < 4)
		{
			if (col_3x3 == col)
				continue ;
			new_m3x3._[row_2x2][col_2x2++] = m4x4._[row_3x3][col_3x3];
		}
		++row_2x2;
		col_2x2 = 0;
	}
	return (new_m3x3);
}

/**
 * @param m2x2	2 by 2 matrix to calculate determinant for
 *
 * @returns	The determinant of a 2x2 matrix
 */
static inline t_flt	det_m2x2(t_m2x2 m2x2)
{
	return (m2x2._[0][0] * m2x2._[1][1] - m2x2._[0][1] * m2x2._[1][0]);
}

/**
 * @param m3x3	3 by 3 matrix to calculate determinant for
 *
 * @returns	The determinant of a 3x3 matrix
 */
t_flt	det_m3x3(t_m3x3 m3x3)
{
	t_m2x2	sub;
	t_flt	det;

	det = 0;
	sub = sub_m3x3(m3x3, 0, 0);
	det += m3x3._[0][0] * det_m2x2(sub);
	sub = sub_m3x3(m3x3, 0, 1);
	det -= m3x3._[0][1] * det_m2x2(sub);
	sub = sub_m3x3(m3x3, 0, 2);
	det += m3x3._[0][2] * det_m2x2(sub);
	return (det);
}

/**
 * @param m4x4	4 by 4 matrix to calculate determinant for
 *
 * @returns	The determinant of a 4x4 matrix
 */
t_flt	det_m4x4(t_m4x4 m4x4)
{
	t_m3x3	sub;
	t_flt	det;

	det = 0;
	sub = sub_m4x4(m4x4, 0, 0);
	det += m4x4._[0][0] * det_m3x3(sub);
	sub = sub_m4x4(m4x4, 0, 1);
	det -= m4x4._[0][1] * det_m3x3(sub);
	sub = sub_m4x4(m4x4, 0, 2);
	det += m4x4._[0][2] * det_m3x3(sub);
	sub = sub_m4x4(m4x4, 0, 3);
	det -= m4x4._[0][3] * det_m3x3(sub);
	return (det);
}
