/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/25 17:02:44 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * @returns A pointer to the program's data.
 * 
 */
t_data	*get_data(void)
{
	static t_data	minirt;

	return (&minirt);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		print_err("program must be provided a single argument");
		return (1);
	}
	if (!parse_scene(argv[1]))
	{
		free_data();
		return (1);
	}
	free_data();
	return (0);
}
