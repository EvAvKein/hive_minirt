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
 * @returns	New matrix that which has elements corresponding to m4x4, each
 *			scaled by scalar
 */
t_m4x4	scaled_m4x4(t_m4x4 m4x4, t_flt scalar)
{
	t_m4x4	scaled;

	scaled._[0][0] = scalar * m4x4._[0][0];
	scaled._[0][1] = scalar * m4x4._[0][1];
	scaled._[0][2] = scalar * m4x4._[0][2];
	scaled._[0][3] = scalar * m4x4._[0][3];
	scaled._[1][0] = scalar * m4x4._[1][0];
	scaled._[1][1] = scalar * m4x4._[1][1];
	scaled._[1][2] = scalar * m4x4._[1][2];
	scaled._[1][3] = scalar * m4x4._[1][3];
	scaled._[2][0] = scalar * m4x4._[2][0];
	scaled._[2][1] = scalar * m4x4._[2][1];
	scaled._[2][2] = scalar * m4x4._[2][2];
	scaled._[2][3] = scalar * m4x4._[2][3];
	scaled._[3][0] = scalar * m4x4._[3][0];
	scaled._[3][1] = scalar * m4x4._[3][1];
	scaled._[3][2] = scalar * m4x4._[3][2];
	scaled._[3][3] = scalar * m4x4._[3][3];
	return (scaled);
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
