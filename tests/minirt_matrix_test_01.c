/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_matrix_test_01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:33:53 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/21 13:34:43 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include <stdio.h>

typedef float	t_flt;

typedef struct t_m4x4
{
	t_flt	_[4][4];
}	t_m4x4;

typedef struct s_axis
{
	t_flt	x;
	t_flt	y;
	t_flt	z;
	t_flt	w;
}	t_axis;

typedef union u_vec4
{
	t_flt	idx[4];
	t_axis	axis;
}	t_vec4;

void	test_function(void)
{
	t_vec4	test;
	test.axis.x = 0;
	test.idx[0] = 3;
	test.axis = (t_axis){.x = 1, .y = 2, .z = 3, .w = 1};
}

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

t_vec4	*scale_vector_in_place(t_flt scalar, t_vec4 *vec)
{
	vec->_[0] = scalar * vec->_[0];
	vec->_[1] = scalar * vec->_[1];
	vec->_[2] = scalar * vec->_[2];
	return (vec);
}

t_vec4	new_scaled_vector(t_flt scalar, t_vec4 const *vec)
{
	t_vec4	new;

	new._[0] = scalar * vec->_[0];
	new._[1] = scalar * vec->_[1];
	new._[2] = scalar * vec->_[2];
	new._[3] = 0;
	return (new);
}

t_vec4	new_transformed_vector(t_m4x4 const *mat, t_vec4 const *vec)
{
	t_vec4	new;

	new._[00] = mat->_[0][0] * vec->_[0];
	new._[0] += mat->_[0][1] * vec->_[1];
	new._[0] += mat->_[0][2] * vec->_[2];
	new._[0] += mat->_[0][3] * vec->_[3];
	new._[01] = mat->_[1][0] * vec->_[0];
	new._[1] += mat->_[1][1] * vec->_[1];
	new._[1] += mat->_[1][2] * vec->_[2];
	new._[1] += mat->_[1][3] * vec->_[3];
	new._[02] = mat->_[2][0] * vec->_[0];
	new._[2] += mat->_[2][1] * vec->_[1];
	new._[2] += mat->_[2][2] * vec->_[2];
	new._[2] += mat->_[2][3] * vec->_[3];
	new._[03] = mat->_[3][0] * vec->_[0];
	new._[3] += mat->_[3][1] * vec->_[1];
	new._[3] += mat->_[3][2] * vec->_[2];
	new._[3] += mat->_[3][3] * vec->_[3];
	return (new);
}

t_vec4	*transform_vector_in_place(t_m4x4 const *mat, t_vec4 *vec)
{
	t_vec4	original;

	original = *vec;
	vec->_[00] = mat->_[0][0] * original._[0];
	vec->_[0] += mat->_[0][1] * original._[1];
	vec->_[0] += mat->_[0][2] * original._[2];
	vec->_[0] += mat->_[0][3] * original._[3];
	vec->_[01] = mat->_[1][0] * original._[0];
	vec->_[1] += mat->_[1][1] * original._[1];
	vec->_[1] += mat->_[1][2] * original._[2];
	vec->_[1] += mat->_[1][3] * original._[3];
	vec->_[02] = mat->_[2][0] * original._[0];
	vec->_[2] += mat->_[2][1] * original._[1];
	vec->_[2] += mat->_[2][2] * original._[2];
	vec->_[2] += mat->_[2][3] * original._[3];
	vec->_[03] = mat->_[3][0] * original._[0];
	vec->_[3] += mat->_[3][1] * original._[1];
	vec->_[3] += mat->_[3][2] * original._[2];
	vec->_[3] += mat->_[3][3] * original._[3];
	return (vec);
}

t_m4x4	identity_matrix = {._ = {	{1, 0, 0, 0},
									{0, 1, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1}}};

void	print_matrix(t_m4x4 const *matrix)
{
	printf("\n%10.2f%10.2f%10.2f%10.2f",		matrix->_[0][0],
												matrix->_[0][1],
												matrix->_[0][2],
												matrix->_[0][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f",		matrix->_[1][0],
												matrix->_[1][1],
												matrix->_[1][2],
												matrix->_[1][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f",		matrix->_[2][0],
												matrix->_[2][1],
												matrix->_[2][2],
												matrix->_[2][3]);
	printf("\n%10.2f%10.2f%10.2f%10.2f\n\n",	matrix->_[3][0],
												matrix->_[3][1],
												matrix->_[3][2],
												matrix->_[3][3]);
}

void	print_vector(t_vec4 const *vector)
{
	printf("\n%6.2f",		vector->_[0]);
	printf("\n%6.2f",		vector->_[1]);
	printf("\n%6.2f",		vector->_[2]);
	printf("\n%6.2f\n\n",	vector->_[3]);
}

t_vec4	*normalize_vector(t_vec4 *vec)
{
	t_flt	scale;

	scale = sqrt(vec->_[0] * vec->_[0]
			+ vec->_[1] * vec->_[1]
			+ vec->_[2] * vec->_[2]);
	vec->_[0] = vec->_[0] / scale;
	vec->_[1] = vec->_[1] / scale;
	vec->_[2] = vec->_[2] / scale;
	vec->_[3] = 0;
	return (vec);
}

t_vec4	new_unit_vector(t_vec4 const *vec)
{
	t_vec4	unit;
	t_flt	scale;

	scale = sqrt(vec->_[0] * vec->_[0]
			+ vec->_[1] * vec->_[1]
			+ vec->_[2] * vec->_[2]);
	unit._[0] = vec->_[0] / scale;
	unit._[1] = vec->_[1] / scale;
	unit._[2] = vec->_[2] / scale;
	unit._[3] = 0;
	return (unit);
}

t_flt	dot_product(t_vec4 const *v1, t_vec4 const *v2)
{
	return (v1->_[0] * v2->_[0]
		+ v1->_[1] * v2->_[1]
		+ v1->_[2] * v2->_[2]);
}

t_vec4	cross_product(t_vec4 const *v1, t_vec4 const *v2)
{
	t_vec4	new;

	new._[0] = v1->_[1] * v2->_[2] - v2->_[1] * v1->_[2];
	new._[1] = v1->_[0] * v2->_[2] - v2->_[0] * v1->_[2];
	new._[2] = v1->_[0] * v2->_[1] - v2->_[0] * v1->_[1];
	new._[3] = 0;
	return (new);
}

int	main(void)
{
	t_m4x4	test;
	t_vec4	point;
	t_vec4	vector;
	int		m;
	int		n;

	m = -1;
	while (++m < 4)
	{
		n = -1;
		while (++n < 4)
			test._[m][n] = m * 4 + n;
	}
	print_matrix(&test);
	test = new_mult_matrix(&test, &test);
	print_matrix(&test);
	vector = (t_vec4){._ = {1, 2, 3, 0}};
	print_vector(&vector);
	point = (t_vec4){._ = {1, 2, 3, 1}};
	print_vector(&point);
	test = new_scaled_matrix(3, &identity_matrix);
	print_matrix(&test);
	vector = new_transformed_vector(&test, &vector);
	print_vector(&vector);
	vector = new_unit_vector(&vector);
	print_vector(&vector);
	return (0);
}
