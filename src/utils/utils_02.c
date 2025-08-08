/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:11:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 12:57:00 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Used this function for debugging raycasting.
 *
 * @param str	String containing file name to write data into
 *
 * TODO: Remove function before eval or move to a debug source file
 */
void	write_pixel_rays_to_file(const char *str)
{
	size_t	i;
	int		fds[2];

	fds[0] = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fds[0] < 0)
		return ;
	fds[1] = dup(STDOUT_FILENO);
	dup2(fds[0], STDOUT_FILENO);
	i = -1;
	while (++i < g_data.pixel_count)
		print_vec(g_data.pixel_rays[i].dir);
	fflush(stdout);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
}

/**
 * Attempts to calloc, frees data and exits program if calloc fails.
 *
 * @param nmemb	Number of members to allocate
 * @param size	Size of members to allocate
 *
 * @returns	Void pointer to allocated memory block
 */
void	*xcalloc(size_t nmemb, size_t size)
{
	void	*mem;

	mem = ft_calloc(nmemb, size);
	if (mem == NULL)
	{
		ft_putendl_fd("ERROR: xcalloc: couldn't allocate memory",
			STDERR_FILENO);
		free_data();
		exit(ERROR_ALLOC);
	}
	return (mem);
}
