/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:43:39 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/11 20:57:08 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	The total size of the file to be created,
 * 			or `0` if a file of the resulting size is not possible.
 */
static uint32_t	calc_file_size(uint32_t header_size,
	uint32_t img_width, uint32_t img_height)
{
	const uint32_t	pixel_count = img_width * img_height;
	const uint32_t	size_per_pixel = 8 * 4;
	const uint32_t	pixels_size = pixel_count * size_per_pixel;

	if (!header_size || !img_height || !img_width)
		return (0);
	if (img_height > UINT32_MAX / img_width
		|| img_width > UINT32_MAX / img_height)
		return (0);
	if (header_size > UINT32_MAX - pixels_size)
		return (0);
	return (header_size + pixels_size);
}

/**
 * Write a bmp header to the provided file descriptor,
 * including the provided image width and height.
 *
 * @returns Whether writing was successful.
 */
static bool	write_header_to_file(int fd,
	uint32_t img_width, uint32_t img_height)
{
	const uint32_t			header_size
		= sizeof(t_bmp_fileheader) + sizeof(t_bmp_infoheader);
	const uint32_t			file_size
		= calc_file_size(header_size, img_width, img_height);
	const t_bmp_fileheader	file_header = {
		.file_type = 0x4D42, .file_size = file_size,
		.bitmap_offset = header_size
	};
	const t_bmp_infoheader	info_header = {
		.size = sizeof(t_bmp_infoheader),
		.width = img_width, .height = img_height,
		.color_planes = 1,
		.bits_per_pixel = 32,
		.compression = 0,
		.size_of_bitmap = file_size - header_size,
		.horizontal_ppm = 0, .vertical_ppm = 0,
		.colors_used = 0, .colors_important = 0,
	};

	if (file_size == 0)
		return (print_err("Image is too large to fit in a '.bmp' file"));
	if (write(fd, &file_header, sizeof(file_header)) < 0
		|| write(fd, &info_header, sizeof(info_header)) < 0)
		return (print_err("Failed to write bmp header into image file"));
	return (true);
}

/**
 * Write the current image's colors to the provided file descriptor.
 */
static bool	write_colors_to_file(int fd)
{
	const uint8_t	*color_channels = g_data.img->pixels;
	size_t			i;
	size_t			row_i;
	t_8bit_color	*pixels_row;

	pixels_row = ft_calloc(g_data.img->width, sizeof(t_8bit_color));
	if (!pixels_row)
		return (print_err("Image saving failed to buffer allocation failure"));
	i = g_data.pixel_count;
	while (i > 0)
	{
		row_i = g_data.img->width + 1;
		while (--row_i > 0)
		{
			pixels_row[row_i - 1].r = color_channels[(i - 1) * 4 + 2];
			pixels_row[row_i - 1].g = color_channels[(i - 1) * 4 + 1];
			pixels_row[row_i - 1].b = color_channels[(i - 1) * 4];
			pixels_row[row_i - 1].a = 0xff;
			--i;
		}
		if (write(fd, pixels_row, g_data.img->width * sizeof(t_8bit_color)) < 0)
			return (free(pixels_row),
				print_err("Failed to write colors into image file"));
	}
	return (free(pixels_row), true);
}

/**
 * Saves the currently rendered image to the provided path in a bitmap format.
 */
void	image_to_file(void)
{
	int		fd;
	char	*file_name;

	if (!g_data.img)
		return ((void) print_err("Image unavailable, unable to save to file"));
	file_name = get_available_file_name();
	if (!file_name)
		return ;
	fd = open(file_name, O_CREAT | O_WRONLY, 0776);
	if (fd < 0)
	{
		free(file_name);
		print_err("Cannot save image to file - cannot create/access file");
		return ;
	}
	if (write_header_to_file(fd, g_data.img->width, g_data.img->height)
		&& write_colors_to_file(fd))
		ft_dprintf(STDIN_FILENO,
			"Screenshot saved to file \"%s\"\n", file_name);
	else
		ft_dprintf(STDERR_FILENO,
			"Error\nFailed to write image data to file \"%s\n", file_name);
	free(file_name);
	close(fd);
}
