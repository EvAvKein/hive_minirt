/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:15:21 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/08 10:08:10 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Multiplies matrix m4x4 in place by the matrix named mult.
 *
 * @returns	Address of m4x4
 */
t_m4x4	*multiply_m4x4(t_m4x4 const *mult, t_m4x4 *m4x4)
{
	int		m;
	t_m4x4	original;

	original = *m4x4;
	m = -1;
	while (++m < 4)
	{
		m4x4->_[m][00] = mult->_[m][0] * original._[0][0];
		m4x4->_[m][0] += mult->_[m][1] * original._[1][0];
		m4x4->_[m][0] += mult->_[m][2] * original._[2][0];
		m4x4->_[m][0] += mult->_[m][3] * original._[3][0];
		m4x4->_[m][01] = mult->_[m][0] * original._[0][1];
		m4x4->_[m][1] += mult->_[m][1] * original._[1][1];
		m4x4->_[m][1] += mult->_[m][2] * original._[2][1];
		m4x4->_[m][1] += mult->_[m][3] * original._[3][1];
		m4x4->_[m][02] = mult->_[m][0] * original._[0][2];
		m4x4->_[m][2] += mult->_[m][1] * original._[1][2];
		m4x4->_[m][2] += mult->_[m][2] * original._[2][2];
		m4x4->_[m][2] += mult->_[m][3] * original._[3][2];
		m4x4->_[m][03] = mult->_[m][0] * original._[0][3];
		m4x4->_[m][3] += mult->_[m][1] * original._[1][3];
		m4x4->_[m][3] += mult->_[m][2] * original._[2][3];
		m4x4->_[m][3] += mult->_[m][3] * original._[3][3];
	}
	return (m4x4);
}

/**
 * @returns	Matrix that is the result of matrix multiplication between
 *			m4x4_1 and m4x4_2
 */
t_m4x4	mult_m4x4(t_m4x4 m4x4_1, t_m4x4 m4x4_2)
{
	int		m;
	t_m4x4	res;

	m = -1;
	while (++m < 4)
	{
		res._[m][00] = m4x4_1._[m][0] * m4x4_2._[0][0];
		res._[m][0] += m4x4_1._[m][1] * m4x4_2._[1][0];
		res._[m][0] += m4x4_1._[m][2] * m4x4_2._[2][0];
		res._[m][0] += m4x4_1._[m][3] * m4x4_2._[3][0];
		res._[m][01] = m4x4_1._[m][0] * m4x4_2._[0][1];
		res._[m][1] += m4x4_1._[m][1] * m4x4_2._[1][1];
		res._[m][1] += m4x4_1._[m][2] * m4x4_2._[2][1];
		res._[m][1] += m4x4_1._[m][3] * m4x4_2._[3][1];
		res._[m][02] = m4x4_1._[m][0] * m4x4_2._[0][2];
		res._[m][2] += m4x4_1._[m][1] * m4x4_2._[1][2];
		res._[m][2] += m4x4_1._[m][2] * m4x4_2._[2][2];
		res._[m][2] += m4x4_1._[m][3] * m4x4_2._[3][2];
		res._[m][03] = m4x4_1._[m][0] * m4x4_2._[0][3];
		res._[m][3] += m4x4_1._[m][1] * m4x4_2._[1][3];
		res._[m][3] += m4x4_1._[m][2] * m4x4_2._[2][3];
		res._[m][3] += m4x4_1._[m][3] * m4x4_2._[3][3];
	}
	return (res);
}

/**
 * Scales the matrix m4x4 in place by scalar.
 *
 * @returns	Address of m4x4
 */
t_m4x4	*scale_m4x4(t_m4x4 *m4x4, t_flt scalar)
{
	m4x4->_[0][0] = scalar * m4x4->_[0][0];
	m4x4->_[0][1] = scalar * m4x4->_[0][1];
	m4x4->_[0][2] = scalar * m4x4->_[0][2];
	m4x4->_[0][3] = scalar * m4x4->_[0][3];
	m4x4->_[1][0] = scalar * m4x4->_[1][0];
	m4x4->_[1][1] = scalar * m4x4->_[1][1];
	m4x4->_[1][2] = scalar * m4x4->_[1][2];
	m4x4->_[1][3] = scalar * m4x4->_[1][3];
	m4x4->_[2][0] = scalar * m4x4->_[2][0];
	m4x4->_[2][1] = scalar * m4x4->_[2][1];
	m4x4->_[2][2] = scalar * m4x4->_[2][2];
	m4x4->_[2][3] = scalar * m4x4->_[2][3];
	m4x4->_[3][0] = scalar * m4x4->_[3][0];
	m4x4->_[3][1] = scalar * m4x4->_[3][1];
	m4x4->_[3][2] = scalar * m4x4->_[3][2];
	m4x4->_[3][3] = scalar * m4x4->_[3][3];
	return (m4x4);
}

/**
 * @returns	New matrix that which has elements corresponding to m4x4, each
 *			scaled by scalar
 */
t_m4x4	scaled_m4x4(t_m4x4 m4x4, t_flt scalar)
{
	t_m4x4	res;

	res._[0][0] = scalar * m4x4._[0][0];
	res._[0][1] = scalar * m4x4._[0][1];
	res._[0][2] = scalar * m4x4._[0][2];
	res._[0][3] = scalar * m4x4._[0][3];
	res._[1][0] = scalar * m4x4._[1][0];
	res._[1][1] = scalar * m4x4._[1][1];
	res._[1][2] = scalar * m4x4._[1][2];
	res._[1][3] = scalar * m4x4._[1][3];
	res._[2][0] = scalar * m4x4._[2][0];
	res._[2][1] = scalar * m4x4._[2][1];
	res._[2][2] = scalar * m4x4._[2][2];
	res._[2][3] = scalar * m4x4._[2][3];
	res._[3][0] = scalar * m4x4._[3][0];
	res._[3][1] = scalar * m4x4._[3][1];
	res._[3][2] = scalar * m4x4._[3][2];
	res._[3][3] = scalar * m4x4._[3][3];
	return (res);
}

void	print_m4x4(t_m4x4 m4x4)
{
	printf("\n%10.2f%10.2f%10.2f%10.2f",
		m4x4._[0][0], m4x4._[0][1], m4x4._[0][2], m4x4._[0][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f",
		m4x4._[1][0], m4x4._[1][1], m4x4._[1][2], m4x4._[1][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f",
		m4x4._[2][0], m4x4._[2][1], m4x4._[2][2], m4x4._[2][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f\n\n",
		m4x4._[3][0], m4x4._[3][1], m4x4._[3][2], m4x4._[3][3]);
}
