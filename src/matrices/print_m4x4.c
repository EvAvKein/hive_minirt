/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_m4x4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:15:21 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/24 10:50:09 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
