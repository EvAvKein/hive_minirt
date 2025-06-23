/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:16:54 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/23 20:32:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
static bool	process_line(char *line)
{
	size_t	i;

	i = 0;
	skip_spaces(line, &i);
	if (line[i] == 'A' && is_space(line[i + 1]))
	{
		if (get_data()->elems.ambient_light)
			return (false);
		return (ambient_light_parse(line, &i));
	}
	if (line[i] == 'C' && is_space(line[i + 1]))
	{
		if (get_data()->elems.camera)
			return (false);
		return (camera_parse(line, &i));
	}
	if (line[i] == 'L' && is_space(line[i + 1]))
		return (light_parse(line, &i));
	if (!ft_strncmp(&line[i], "sp", 2) && is_space(line[i + 2]))
		return (sphere_parse(line, &i));
	if (!ft_strncmp(&line[i], "pl", 2) && is_space(line[i + 2]))
		return (plane_parse(line, &i));
	if (!ft_strncmp(&line[i], "cy", 2) && is_space(line[i + 2]))
		return (cylinder_parse(line, &i));
	return (false);
}

/**
 * 
 * TODO: Write docs & validation error messages 
 * 
 */
bool	parse_scene(char *file_path)
{
	const size_t	path_len = ft_strlen(file_path);
	int				fd;
	char			*line;
	
	if (path_len < 3 || ft_strncmp(&file_path[path_len - 3], ".rt", 3))
		return (print_err("Provided file path must end with \".rt\""), false);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_err("Failed to open the provided file"), false);
	while (true)
	{
		if (!set_next_line(fd, &line))
		{
			close(fd);
			return (print_err("Failed to read from the provided file"), false);
		}
		if (!line)
			break ;
		if (!process_line(line))
			return (close(fd), false);
	}
	close(fd);
	return (true);
}
