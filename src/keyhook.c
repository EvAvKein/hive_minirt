/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:11:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/11 10:21:43 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	keyhook(mlx_key_data_t key_data, void *param)
{
	(void) key_data;
	(void) param;

	if (key_data.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(get_data()->mlx);
		free_data();
		exit(EXIT_SUCCESS);
	}
}

