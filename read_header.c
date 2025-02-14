/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:21:43 by samartin          #+#    #+#             */
/*   Updated: 2025/02/13 13:26:31 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

/**
 * Allocates and populates an array with specific strings, ending with a NULL
 *  pointer.
 * 
 * @return The array containing the keywords.
 */
static char	**c3d_populate_kw(void)
{
	char	**kwords;

	kwords = malloc(7 * sizeof(char *));
	if (!kwords)
		c3d_fatal_errors(-1);
	kwords[0] = ft_strdup("NO ");
	kwords[1] = ft_strdup("EA ");
	kwords[2] = ft_strdup("SO ");
	kwords[3] = ft_strdup("WE ");
	kwords[4] = ft_strdup("F ");
	kwords[5] = ft_strdup("C ");
	kwords [6] = NULL;
	return (kwords);
}

/**
 * Parses a line of text removing unwanted whitespaces, checks for keywords,
 *  and updates a header array based on the keyword found.
 * 
 * @param line The string received from a line in the .cub file.
 * @param header An array of strings, it comes from the heap (un-malloced) and
 *  stores the expected six lines of header fromthe .cub file.
 * @param line_flags Signals binarily the presence of each line in the header.
 *  Each bit in this variable corresponds to a specific keyword that is
 *  compared with the content of the line.
 * @return The value of the keyword found.
 */
static uint8_t	c3d_add_line(char *line, char **header, uint8_t l_flags)
{
	char	**kwords;
	int		y;

	y = 0;
	kwords = c3d_populate_kw();
	line = ft_strtrim(line, " \t\v\n\r\f");
	while (kwords[y])
	{
		if (!ft_strncmp(line, kwords[y], 3) || \
			((!ft_strncmp(line, kwords[y], 2) && y > 3)))
		{
			if ((1 << y) & l_flags)
			{
				free(line);
				return (c3d_free2d(kwords), c3d_clear_header(header));
			}
			header[y] = ft_strtrim(line + 2, " \t\v\n\r\f");
			free(line);
			return (c3d_free2d(kwords), 1 << y);
		}
		y++;
	}
	if (*line != '\0')
		return (free(line), c3d_free2d(kwords), c3d_clear_header(header));
	return (free(line), c3d_free2d(kwords));
}

/**
 * Loads from XPM files MLX textures for walls storing them into the a map
 *  struct.
 * 
 * @param map The `t_map` structure pointer witch will store the images.
 * @param header A pointer to an array of strings that contains the file paths
 *  of the textures for the map.
 * @param mlx The pointer to the mlx controller struct.
 * 
 * @return 1 if the map parameter was NULL or a image could not be loaded from
 *  the path given, 0 if all worked fine.
 */
static uint8_t	c3d_load_textures(t_map *map, char **header, t_mlx *mlx)
{
	int		i;

	i = 0;
	if (!map)
		return (1);
	while (i < 4)
	{
printf("%s\n", header[i]);
		map->walls[i].img = (t_mlximg *)mlx_xpm_file_to_image(mlx, header[i], \
			&(map->walls[i].wd), &(map->walls[i].ht));
		if (!(map->walls[i].img))
			return (1);
		map->walls[i].addr = (int *)mlx_get_data_addr(map->walls[i].img,
				&(map->walls[i].bits_per_pixel), &(map->walls[i].line_length),
				&(map->walls[i].endian));
		i++;
	}
	return (0);
}

/**
 * Assigns floor and ceiling colors to a map structure based on RGB values
 *  provided in the header. The floor is always stored in the index 4 and the
 *  ceiling in the index 5.
 * 
 * @param map A pointer to a `t_map` struct that will store the two colors.
 * @param header The array of string built in cb_read_header which contains the
 *  two lines to be parsed into rgb value.
 * @return 1 if the map parameter was NULL or the color fields were unreadable.
 *  0 If all worked fine.
 */
static uint8_t	c3d_assign_colors(t_map *map, char **header)
{
	char	**rgbs;

	if (!map)
		return (1);
	rgbs = ft_split(header[4], ',');
	if (!c3d_matrix_health_3(rgbs))
		return (1);
	map->floor_color = ((ft_atoi(rgbs[0])) << 16 | ft_atoi(rgbs[1]) << 8 | \
		ft_atoi(rgbs[2]));
	c3d_free2d(rgbs);
	rgbs = ft_split(header[5], ',');
	if (!c3d_matrix_health_3(rgbs))
		return (1);
	map->ceil_color = ((ft_atoi(rgbs[0])) << 16 | ft_atoi(rgbs[1]) << 8 | \
		ft_atoi(rgbs[2]));
	c3d_free2d(rgbs);
	return (0);
}

/**
 * Reads and processes header information from a file descriptor. `Line flags`
 *  controls that there are exactly one of each expected line. A correct header
 *  should end with a 63 flag (111111 in binary). The `cb_add_line` auxiliary
 *  function would return a greater number if it finds a repeated or not valid
 *  line.
 * @param fd The file descriptor of the file being read.
 * @param map A pointer to a `t_map` struct.
 * @return 1 in case the flags reveal an incorrect header or EOF is reached
 *  with `get_next_line`, 0 if all worked fine.
 */
uint8_t	c3d_read_header(int fd, t_map *map, t_mlx *mlx)
{
	char	*line;
	char	*header[6];
	uint8_t	line_flags;

	line_flags = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (line)
		{
			line_flags += c3d_add_line(line, header, line_flags);
			free(line);
			if (line_flags >= 64)
				return (c3d_clear_header(header));
			else if (line_flags == 63)
				break ;
		}
		else
			return (1);
	}
	if (c3d_load_textures(map, header, mlx))
		return (c3d_clear_header(header));
	else if (c3d_assign_colors(map, header))
		return (c3d_clear_header(header));
	return (c3d_clear_header(header), 0);
}
