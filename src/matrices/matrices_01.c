/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:15:21 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 09:45:37 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
 * Function for print debugging and inspecting matrices easily.
 *
 * @param m4x4	4 by 4 matrix to print
 *
 * Prints a 4 by 4 matrix with whitespace around.
 */
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
