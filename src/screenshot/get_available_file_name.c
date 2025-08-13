/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_available_file_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:20:32 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/11 20:56:21 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	increment_postfixed_num(char *buffer);

/**
 * @returns A heap-allocated path to the next creatable screenshot file
 *          (or `NULL` on memory allocation failure).
 */
char	*get_available_file_name(void)
{
	char	name[40];
	size_t	i;
	char	*name_on_heap;

	ft_bzero(name, 40);
	ft_strlcpy(name, "miniRT_screenshot_0.bmp", 24);
	while (!access(name, F_OK))
	{
		i = ft_strlen(name) - 4;
		while (name[i])
			name[i++] = '\0';
		increment_postfixed_num(name);
		ft_memcpy(ft_strchr(name, '\0'), ".bmp", 5);
	}
	name_on_heap = ft_strdup(name);
	if (!name_on_heap)
		print_err("File name string allocation failed");
	return (name_on_heap);
}

/**
 * Increments the character-based number at the end of the provided string.
 *
 * @param buffer The array in which increment the number
 *               according to its digit characters.
 *               Assumed to contain at least one leading non-space character,
 *               at least one digit,
 *               and assumed to have enough space for all necessary digits.
 */
static void	increment_postfixed_num(char *buffer)
{
	size_t	i;

	i = ft_strlen(buffer) - 1;
	if (buffer[i] < '9')
	{
		buffer[i]++;
		return ;
	}
	while (buffer[i] == '9')
	{
		if (!ft_isdigit(buffer[i - 1]))
		{
			buffer[i++] = '1';
			while (buffer[i])
				buffer[i++] = '0';
			break ;
		}
		buffer[i--] = '0';
	}
	if (!buffer[i])
		buffer[i] = '0';
	else
		buffer[i]++;
}
