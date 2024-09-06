/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:03:15 by samartin          #+#    #+#             */
/*   Updated: 2024/09/06 12:39:50 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cb_skip_ws(char *line)
{
	while (line && *line && ft_isspace(*line))
		line++;
	return (line);
}

char	**cb_populate_kw(void)
{
	char	**kwords;

	kwords = malloc(7 * sizeof(char *));
	if (!kwords)
		cb_fatal_errors(-1);
	kwords[0] = ft_strdup("NO ");
	kwords[1] = ft_strdup("EA ");
	kwords[2] = ft_strdup("SO ");
	kwords[3] = ft_strdup("WE ");
	kwords[4] = ft_strdup("F ");
	kwords[5] = ft_strdup("C ");
	kwords [6] = NULL;
	return (kwords);
}

void	cb_free2d(char **array_of_str)
{
	int	i;

	i = 0;
	while (array_of_str[i])
	{
		free(array_of_str[i]);
		i++;
	}
	free(array_of_str);
}

__uint8_t	cb_clear_header(char **header, char **kwords)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (header[i])
			free(header[i]);
		i++;
	}
	cb_free2d(kwords);
	return (255);
}

/** REWRITE
 * The function `cb_add_line` parses a line of text to extract specific keywords and store them in a
 * header array based on predefined conditions.
 * 
 * @param line The `line` parameter is a pointer to a character array that represents a line of text.
 * @param header The `header` parameter is a pointer to a pointer to a character array. It is used to
 * store header information extracted from the input line in the `cb_add_line` function.
 * @param line_flags The `line_flags` parameter is a variable of type `uint8_t` that is used to store
 * flags indicating certain properties or characteristics of a line in a map. Each bit in the
 * `line_flags` variable corresponds to a specific flag, and the value of the bit (0 or 1
 * 
 * @return The function `cb_add_line` is returning either `0`, `1 << i`, or the result of calling
 * `cb_clear_header(header, kwords)`.
 */
__uint8_t	cb_add_line(char *line, char **header, __uint8_t line_flags)
{
	char	**kwords;
	int		i;

	i = 0;
	kwords = cb_populate_kw();
	line = cb_skip_ws(line);
	while (kwords[i])
	{
		if (!ft_strncmp(line, kwords[i], 3) || ((!ft_strncmp(line, kwords[i], 2) \
			&& i > 3)))
		{
			if ((1 << i) & line_flags)
				return (cb_clear_header(header, kwords));
			line = cb_skip_ws(line + 2);
			header[i] = ft_strdup(line);
			return (1 << i);
		}
		i++;
	}
	if (*line != '\n')
		return (cb_clear_header(header, kwords));
	return (0);
}

/**
 * Loads textures from PNG files and adds them to linked lists using
 * `mlx_load_png`.
 * @param map Loads textures from PNG files and adding them to linked lists
 *  that are contained inside another linked list.
 * @param header An array of strings. Each string in the first four indexes
 *  contains the file path of a texture image, loads the corresponding texture 
 * @return The same pointer that was received.
 */
/* 
t_map	*cb_load_textures(t_map *map, char **header)
{
	int			i;
	t_texture	*texture;
	t_list		*maplst;
	t_list		*txlst;
	t_list		*node;

	i = 0;
	while (i < 4)
	{
		texture = mlx_xpm_file_to_image(header[i]);
		if (!texture)
			return (cb_errors(3), NULL);
		node = ft_lstnew(texture);
		if (!node)
			cb_fatal_errors(1);
		ft_lstadd_back(&txlst, node);
		node = ft_lstnew(txlst);
		if (!node)
			cb_fatal_errors(1);
		ft_lstadd_back(&maplst, node);
		i++;
	}
	return (map);
} */

t_map	*cb_save_texture_paths(t_map *map, char** header)
{
	t_list	*node;
	int		i;

	i = 0;
	while (i < 4)
	{
		node = ft_lstnew(header[i]);
		if (!node)
			cb_fatal_errors(1);
		ft_lstadd_back(&(map->txtr_lst), node);
		i++;
	}
	return (map);
}

/**
 * Assigns floor and ceiling colors to a map structure based on RGB values
 *  provided in the header. The floor is always stored in the index 4 and the
 *  ceiling in the index 5.
 * 
 * @param map A pointer to a `t_map` struct that will store the two colors.
 * @param header The array of string built in cb_read_header which contains the
 *  two lines to be parsed into rgb value.
 * @return The same pointer that was received.
 */
t_map	*cb_assign_colors(t_map *map, char **header)
{
	char	**rgbs;

	rgbs = ft_split(header[4], ',');
	if (!rgbs)
		cb_fatal_errors(1);
	map->floor_color = ((ft_atoi(rgbs[0])) << 24 | ft_atoi(rgbs[1]) << 16 | \
		ft_atoi(rgbs[2]) << 8);
	if (rgbs[3])
		map->floor_color |= ft_atoi(rgbs[3]);
	cb_free2d(rgbs);
	rgbs = ft_split(header[5], ',');
	if (!rgbs)
		cb_fatal_errors(1);
	map->ceil_color = ((ft_atoi(rgbs[0])) << 24 | ft_atoi(rgbs[1]) << 16 | \
		ft_atoi(rgbs[2]) << 8);
	if (rgbs[3])
		map->floor_color |= ft_atoi(rgbs[3]);
	cb_free2d(rgbs);
	return (map);
}

/**
 * Reads and processes header information from a file descriptor. `Line flags`
 *  controls that there are exactly one of each expected line. A correct header
 *  should end with a 63 flag (111111 in binary). The `cb_add_line` auxiliary
 *  function would return a greater number if it finds a repeated or not valid
 *  line.
 * @param fd The file descriptor of the file being read.
 * @param map A pointer to a `t_map` struct.
 * @return The same pointer that was received, or NULL in case the flags reveal
 *  an incorrect header or EOF is reached with `get_next_line`.
 */
t_map	*cb_read_header(int fd, t_map *map)
{
	char		*line;
	char		*header[6];
	__uint8_t	line_flags;

	line_flags = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (line)
		{
			line_flags += cb_add_line(line, header, line_flags);
			free(line);
			if (line_flags >= 64)
				return (NULL);
			else if (line_flags == 63)
				break ;
		}
		else
			return (NULL);
	}
	map = cb_save_texture_paths(map, header);
	map = cb_assign_colors(map, header);
	return (map);
}

/**
 * Converts a list representation of a map into a matrix representation. it
 *  sets each array position to the content of each node of the list. The list
 *  is freed with the `ft_list_clear` function with no function pointer to
 *  remove the data (as the strings have been moved directly as pointers to
 *  the matrix).
 * @param map A pointer to a `t_map` struct.
 * @param map_as_list A linked list containing strings. The `t_list` type defines
 *  its content as a union, and we use the `.str` member in this case.
 * @return The same pointer that was received unless it has been nullified by
 *  an error.
 */
t_map	*cb_map_list_to_matrix(t_map *map, t_list *map_as_list)
{
	size_t	i;

	map->map_size[0] = 0;
	map->map_size[1] = ft_lstsize(map_as_list);
	map->map_matrix = malloc(map->map_size[1] * sizeof(char *));
	if (!(map->map_matrix))
		cb_fatal_errors(1);
	i = 0;
	while (i < map->map_size[1])
	{
		map->map_matrix[i] = (map_as_list->content.str);
		if (ft_strlen(map->map_matrix[i]) > map->map_size[0])
			map->map_size[0] = ft_strlen(map->map_matrix[i]);
		i++;
	}
	ft_lstclear(&map_as_list, NULL);
	return (map);
}

/**
 * The function `cb_read_map` reads a map from a file descriptor, fist stores it
 *  as a list, and once the number of lines is known, converts it to a matrix
 *  and the map pointer is returned.
 * @param fd The file descriptor of the already open file from which the map is
 *  being read. It is used to be read line by line using the `get_next_line`
 *  function.
 * @param map A pointer to the dinamically allocated map struct.
 * @return The same pointer that was received unless it has been nullified by
 *  an error.
 */
t_map	*cb_read_map(int fd, t_map *map)
{
	char	*line;
	t_list	*map_as_list;
	t_list	*node;

	line = get_next_line(fd);
	while (!ft_strncmp(cb_skip_ws(line), "", 1))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		node = ft_lstnew(line);
		if (!node)
			cb_fatal_errors(1);
		ft_lstadd_back(&map_as_list, node);
		line = get_next_line(fd);
	}
	map = cb_map_list_to_matrix(map, map_as_list);
	return (map);
}

/**
 * Opens and reads a map file, extracting first the header information, and then
 *  the map matrix.
 * @param path A string with the file path to the map file.
 * @return The `t_map` structure dinamically allocated in this same function as
 *  a pointer.
 */
t_map	*cb_load_map_file(char *path)
{
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		cb_fatal_errors(1);
	map = cb_read_header(fd, map);
	if (!map)
		return (NULL);
	map = cb_read_map(fd, map);
	return (map);
}

/**
 * Loads a map file and validates its content. First step ensures that there are
 *  only one parameter and that it is a filename ended in `.cub`, then that file
 *  is loaded and then checked if it is a valid map.
 * @param argc The number of arguments passed to the main function when the
 *  program is executed.
 * @param argv The command-line arguments passed to the program as received in
 *  main: an array of strings.
 * @param map A pointer to a `t_map` structure to be filled with the data
 *  loaded from the file indicated by the argumets.
 * @return A positive integer if there was some error, 0 if the work was
 *  successful.
 */
__int8_t	cb_startup(int argc, char **argv, t_map *map)
{
	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (cb_errors(1));
	map = cb_load_map_file(argv[1]);
	if (!map)
		return (cb_errors(2));
	//TO DO: Validate map content
	return (0);
}

//Falta liberar el header en algún punto.