/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:11:08 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/18 17:15:22 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		quicksort(t_ray_x_obj_array *arr, size_t lo, size_t hi);
static size_t	select_pivot(t_ray_x_obj_array const *arr, size_t lo,
					size_t hi);
static void		swap(t_ray_x_obj_array const *arr, size_t i, size_t j);

void	quicksort_ray_intersections(t_ray *ray)
{
	quicksort(&ray->intersections, 0, ray->intersections.idx - 1);
}

// TODO: Consider removing this file before evaluation, not used
static size_t	select_pivot(t_ray_x_obj_array const *arr, size_t lo, size_t hi)
{
	size_t	mid;
	t_flt	t_hi;
	t_flt	t_lo;
	t_flt	t_mid;

	mid = (hi + lo) / 2;
	t_hi = arr->_[hi].t;
	t_lo = arr->_[lo].t;
	t_mid = arr->_[mid].t;
	if ((t_lo > t_mid && t_mid > t_hi) || (t_hi > t_mid && t_mid > t_lo))
		return (mid);
	if ((t_lo > t_hi && t_hi > t_mid) || (t_mid > t_hi && t_hi > t_lo))
		return (hi);
	return (lo);
}

static void	quicksort(t_ray_x_obj_array *arr, size_t lo, size_t hi)
{
	size_t		piv;
	size_t		i;
	size_t		j;

	if (hi <= lo)
		return ;
	piv = select_pivot(arr, lo, hi);
	swap(arr, piv, hi);
	i = lo;
	j = lo - 1;
	while (++j < hi)
	{
		if (arr->_[j].t <= arr->_[hi].t)
		{
			swap(arr, i, j);
			i++;
		}
	}
	swap(arr, i, hi);
	quicksort(arr, lo, i - 1);
	quicksort(arr, i + 1, hi);
}

static void	swap(t_ray_x_obj_array const *arr, size_t i, size_t j)
{
	t_ray_x_obj	tmp;

	if (i == j)
		return ;
	tmp = arr->_[i];
	arr->_[i] = arr->_[j];
	arr->_[j] = tmp;
}
