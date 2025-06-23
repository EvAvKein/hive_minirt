/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:26:46 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/17 10:48:15 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * Prints to STDERR "Error" and a newline,
 * followed by "miniRT: ", two provided strings, and a newline.
 * 
 * @returns The return value of `ft_dprintf`
 *          (amount of characters written, or -1 on write error).
 * 
 */
int	print_err(char *error)
{
	return (ft_dprintf(STDERR_FILENO, "Error\nminiRT: %s\n", error));
}
