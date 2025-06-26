/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:15:21 by jvarila           #+#    #+#             */
/*   Updated: 2025/06/26 15:16:33 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_m4x4	*multiply_matrix_in_place(t_m4x4 const *mult, t_m4x4 *mat)
{
	int		m;
	t_m4x4	original;

	original = *mat;
	m = -1;
	while (++m < 4)
	{
		mat->_[m][00] = mult->_[m][0] * original._[0][0];
		mat->_[m][0] += mult->_[m][1] * original._[1][0];
		mat->_[m][0] += mult->_[m][2] * original._[2][0];
		mat->_[m][0] += mult->_[m][3] * original._[3][0];
		mat->_[m][01] = mult->_[m][0] * original._[0][1];
		mat->_[m][1] += mult->_[m][1] * original._[1][1];
		mat->_[m][1] += mult->_[m][2] * original._[2][1];
		mat->_[m][1] += mult->_[m][3] * original._[3][1];
		mat->_[m][02] = mult->_[m][0] * original._[0][2];
		mat->_[m][2] += mult->_[m][1] * original._[1][2];
		mat->_[m][2] += mult->_[m][2] * original._[2][2];
		mat->_[m][2] += mult->_[m][3] * original._[3][2];
		mat->_[m][03] = mult->_[m][0] * original._[0][3];
		mat->_[m][3] += mult->_[m][1] * original._[1][3];
		mat->_[m][3] += mult->_[m][2] * original._[2][3];
		mat->_[m][3] += mult->_[m][3] * original._[3][3];
	}
	return (mat);
}

t_m4x4	new_mult_matrix(const t_m4x4 *mat1, const t_m4x4 *mat2)
{
	int		m;
	t_m4x4	new;

	m = -1;
	while (++m < 4)
	{
		new._[m][00] = mat1->_[m][0] * mat2->_[0][0];
		new._[m][0] += mat1->_[m][1] * mat2->_[1][0];
		new._[m][0] += mat1->_[m][2] * mat2->_[2][0];
		new._[m][0] += mat1->_[m][3] * mat2->_[3][0];
		new._[m][01] = mat1->_[m][0] * mat2->_[0][1];
		new._[m][1] += mat1->_[m][1] * mat2->_[1][1];
		new._[m][1] += mat1->_[m][2] * mat2->_[2][1];
		new._[m][1] += mat1->_[m][3] * mat2->_[3][1];
		new._[m][02] = mat1->_[m][0] * mat2->_[0][2];
		new._[m][2] += mat1->_[m][1] * mat2->_[1][2];
		new._[m][2] += mat1->_[m][2] * mat2->_[2][2];
		new._[m][2] += mat1->_[m][3] * mat2->_[3][2];
		new._[m][03] = mat1->_[m][0] * mat2->_[0][3];
		new._[m][3] += mat1->_[m][1] * mat2->_[1][3];
		new._[m][3] += mat1->_[m][2] * mat2->_[2][3];
		new._[m][3] += mat1->_[m][3] * mat2->_[3][3];
	}
	return (new);
}

t_m4x4	*scale_matrix_in_place(t_flt scalar, t_m4x4 *mat)
{
	mat->_[0][0] = scalar * mat->_[0][0];
	mat->_[0][1] = scalar * mat->_[0][1];
	mat->_[0][2] = scalar * mat->_[0][2];
	mat->_[0][3] = scalar * mat->_[0][3];
	mat->_[1][0] = scalar * mat->_[1][0];
	mat->_[1][1] = scalar * mat->_[1][1];
	mat->_[1][2] = scalar * mat->_[1][2];
	mat->_[1][3] = scalar * mat->_[1][3];
	mat->_[2][0] = scalar * mat->_[2][0];
	mat->_[2][1] = scalar * mat->_[2][1];
	mat->_[2][2] = scalar * mat->_[2][2];
	mat->_[2][3] = scalar * mat->_[2][3];
	mat->_[3][0] = scalar * mat->_[3][0];
	mat->_[3][1] = scalar * mat->_[3][1];
	mat->_[3][2] = scalar * mat->_[3][2];
	mat->_[3][3] = scalar * mat->_[3][3];
	return (mat);
}

t_m4x4	new_scaled_matrix(t_flt scalar, t_m4x4 const *mat)
{
	t_m4x4	new;

	new._[0][0] = scalar * mat->_[0][0];
	new._[0][1] = scalar * mat->_[0][1];
	new._[0][2] = scalar * mat->_[0][2];
	new._[0][3] = scalar * mat->_[0][3];
	new._[1][0] = scalar * mat->_[1][0];
	new._[1][1] = scalar * mat->_[1][1];
	new._[1][2] = scalar * mat->_[1][2];
	new._[1][3] = scalar * mat->_[1][3];
	new._[2][0] = scalar * mat->_[2][0];
	new._[2][1] = scalar * mat->_[2][1];
	new._[2][2] = scalar * mat->_[2][2];
	new._[2][3] = scalar * mat->_[2][3];
	new._[3][0] = scalar * mat->_[3][0];
	new._[3][1] = scalar * mat->_[3][1];
	new._[3][2] = scalar * mat->_[3][2];
	new._[3][3] = scalar * mat->_[3][3];
	return (new);
}

void	print_matrix(t_m4x4 const *matrix)
{
	printf("\n%10.2f%10.2f%10.2f%10.2f",
		matrix->_[0][0], matrix->_[0][1], matrix->_[0][2], matrix->_[0][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f",
		matrix->_[1][0], matrix->_[1][1], matrix->_[1][2], matrix->_[1][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f",
		matrix->_[2][0], matrix->_[2][1], matrix->_[2][2], matrix->_[2][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f\n\n",
		matrix->_[3][0], matrix->_[3][1], matrix->_[3][2], matrix->_[3][3]);
}
