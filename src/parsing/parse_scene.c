/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:16:54 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/26 11:24:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *
 * Parse the provided line, calling the relevant shape-parsing function.
 * 
 * @param line	The line to be parsed.
 * 
 * @param i		An address to index with which to parse
 * 				(should always start as an address to the value `0`).
 *  
 * @returns Whether line-parsing was successful.
 * 
 */
static bool	process_line(char *line, size_t *i)
{
	skip_spaces(line, i);
	if (line[*i] == '\0')
		return (true);
	if (line[*i] == 'A' && is_space(line[*i + 1]))
	{
		if (get_data()->elems.ambient_light)
			return (print_err("excess ambient light"));
		return (ambient_light_parse(line, i));
	}
	if (line[*i] == 'C' && is_space(line[*i + 1]))
	{
		if (get_data()->elems.camera)
			return (print_err("excess camera"));
		return (camera_parse(line, i));
	}
	if (line[*i] == 'L' && is_space(line[*i + 1]))
		return (light_parse(line, i));
	if (!ft_strncmp(&line[*i], "sp", 2) && is_space(line[*i + 2]))
		return (sphere_parse(line, i));
	if (!ft_strncmp(&line[*i], "pl", 2) && is_space(line[*i + 2]))
		return (plane_parse(line, i));
	if (!ft_strncmp(&line[*i], "cy", 2) && is_space(line[*i + 2]))
		return (cylinder_parse(line, i));
	return (print_err("invalid object name"));
}

/**
 *
 * @param fd	File descriptor of the file to read.
 *  
 * @returns Whether scene-parsing was successful.
 * 
 */
static bool	parsing_loop(int fd)
{
	char	*line;
	size_t	line_i;
	size_t	line_count;

	line_count = 0;
	while (true)
	{
		line_count++;
		line_i = 0;
		if (!set_next_line(fd, &line))
		{
			print_err("Failed to read from the provided file");
			ft_dprintf(STDERR_FILENO, "at line %d\n", line_count);
			return (false);
		}
		if (!line)
			return (true);
		if (!process_line(line, &line_i))
		{
			ft_dprintf(STDERR_FILENO,
				"at line %d, char %i\n", line_count, line_i);
			return (free(line), false);
		}
		free(line);
	}
}

/**
 * 
 * @param file_path	The file path for the scene file to be parsed.
 *
 * @returns Whether scene-parsing was successful.
 *  
 */
bool	parse_scene(char *file_path)
{
	const size_t	path_len = ft_strlen(file_path);
	int				fd;

	if (path_len < 3 || ft_strncmp(&file_path[path_len - 3], ".rt", 3))
		return (print_err("Provided file path must end with \".rt\""), false);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_err("Failed to open the provided file"), false);
	if (!parsing_loop(fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	if (!get_data()->elems.ambient_light
		|| !get_data()->elems.camera
		|| !get_data()->elems.lights)
	{
		print_err("Scene must have"
			" an ambient light, a camera, and at least 1 light");
		return (false);
	}
	return (true);
}
