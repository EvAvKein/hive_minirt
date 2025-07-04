/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:57:20 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/04 10:49:22 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_m4x4	identity_m4x4(void)
{
	static t_m4x4 const	identity = (t_m4x4){
		._[0][0] = 1, ._[1][1] = 1, ._[2][2] = 1, ._[3][3] = 1};

	return (identity);
}

t_m4x4	transpose_m4x4(t_m4x4 const *m4x4)
{
	t_m4x4	transpose;
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			transpose._[i][j] = m4x4->_[j][i];
		}
	}
	return (transpose);
}
