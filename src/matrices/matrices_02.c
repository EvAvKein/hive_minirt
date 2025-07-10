/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:57:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/04 13:42:39 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	A submatrix of a 3x3 matrix, removes row and col from the original
 *			3x3 and packages the remaining elements into a 2x2 matrix, returns
 *			that matrix
 */
t_m2x2	sub_m3x3(t_m3x3 const *m3x3, size_t row, size_t col)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	t_m2x2	new_m2x2;

	i = -1;
	k = 0;
	l = 0;
	while (++i < 3)
	{
		if (i == row)
			continue ;
		j = -1;
		while (++j < 3)
		{
			if (j == col)
				continue ;
			new_m2x2._[k][l++] = m3x3->_[i][j];
		}
		++k;
		l = 0;
	}
	return (new_m2x2);
}

/**
 * @returns	A submatrix of a 4x4 matrix, removes row and col from the original
 *			4x4 and packages the remaining elements into a 2x2 matrix, returns
 *			that matrix
 */
t_m3x3	sub_m4x4(t_m4x4 const *m4x4, size_t row, size_t col)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	t_m3x3	new_m3x3;

	i = -1;
	k = 0;
	l = 0;
	while (++i < 4)
	{
		if (i == row)
			continue ;
		j = -1;
		while (++j < 4)
		{
			if (j == col)
				continue ;
			new_m3x3._[k][l++] = m4x4->_[i][j];
		}
		++k;
		l = 0;
	}
	return (new_m3x3);
}

/**
 * @returns	The determinant of a 2x2 matrix
 */
t_flt	det_m2x2(t_m2x2 const *m2x2)
{
	return (m2x2->_[0][0] * m2x2->_[1][1] - m2x2->_[0][1] * m2x2->_[1][0]);
}

/**
 * @returns	The determinant of a 3x3 matrix
 */
t_flt	det_m3x3(t_m3x3 const *m3x3)
{
	t_m2x2	sub;
	t_flt	det;

	det = 0;
	sub = sub_m3x3(m3x3, 0, 0);
	det += m3x3->_[0][0] * det_m2x2(&sub);
	sub = sub_m3x3(m3x3, 0, 1);
	det -= m3x3->_[0][1] * det_m2x2(&sub);
	sub = sub_m3x3(m3x3, 0, 2);
	det += m3x3->_[0][2] * det_m2x2(&sub);
	return (det);
}

/**
 * @returns	The determinant of a 4x4 matrix
 */
t_flt	det_m4x4(t_m4x4 const *m4x4)
{
	t_m3x3	sub;
	t_flt	det;

	det = 0;
	sub = sub_m4x4(m4x4, 0, 0);
	det += m4x4->_[0][0] * det_m3x3(&sub);
	sub = sub_m4x4(m4x4, 0, 1);
	det -= m4x4->_[0][1] * det_m3x3(&sub);
	sub = sub_m4x4(m4x4, 0, 2);
	det += m4x4->_[0][2] * det_m3x3(&sub);
	sub = sub_m4x4(m4x4, 0, 3);
	det -= m4x4->_[0][3] * det_m3x3(&sub);
	return (det);
}
