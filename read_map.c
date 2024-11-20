/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:23:38 by samartin          #+#    #+#             */
/*   Updated: 2024/10/21 13:44:10 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

/**
 * Frees memory only if the type passed matches a free-able one.
 * 
 * @param content Type `t_content` is a Union that can contain several types,
 *  when passsed to this function, it should be a pointer to data that needs to
 *  be freed.
 * @param vartype Used to determine the type of the variable that needs to
 * be freed.
 */
void	ft_free_envel(t_content content, t_type vartype)
{
	if (vartype == STR || vartype == PTR || vartype == OTHER)
		free(content.ptr);
}

/**
 * Skips any leading white spaces in a given string and returns a pointer to
 * the first non-white space character.
 * 
 * @param line A string where to find the start of non-whitespace characters.
 * 
 * @return The pointer returned is NOT a newly malloced string, but a point
 * from the string start.
 */
char	*c3d_skip_ws(char *line)
{
	while (line && *line && ft_isspace(*line))
		line++;
	return (line);
}

/**
 * Converts a list representation of a map into a 2D matrix representation. it
 *  copies each string in the list to each row of the matrix, adding spaces in
 *  case the line is shorter than the matrix width. The list is afterwards
 *  freed with the `ft_list_clear_type` function with a function enveloping the
 *  regular `free` function.
 * @param map A pointer to a `t_map` struct.
 * @param map_as_list A linked list containing strings. The `t_list` type defines
 *  its content as a union, and we use the `.str` member in this case.
 * @return The same pointer that was received unless it has been nullified by
 *  an error.
 */
t_map	*c3d_map_list_to_matrix(t_map *map, t_list *map_as_list)
{
	size_t	i;
	t_list	*node;

	map->map_size[1] = ft_lstsize(map_as_list);
	map->map_matrix = malloc(map->map_size[1] * sizeof(char *));
	if (!(map->map_matrix))
		c3d_fatal_errors(1);
	i = 0;
	node = map_as_list;
	while (i < map->map_size[1])
	{
		map->map_matrix[i] = malloc((map->map_size[0] + 1) * sizeof(char *));
		c3d_cpynfill(map->map_matrix[i], node->content.str, map->map_size[0]);
		i++;
		node = node->next;
	}
	ft_lstclear_type(&map_as_list, ft_free_envel);
	return (map);
}

/**
 * Sets the X axis size according to the longest line found, removing the `\n`
 *  pre-terminator of the line if there is one.
 * 
 * @param line A string representing one line of the map.
 * @param map_size An array of X and Y sizes. Only the element 0 (X) is to be
 *  modified if the line is longer than a previously found value.
 */
static void	c3d_set_width(char *line, size_t *map_size)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	if (line_len > map_size[0])
		map_size[0] = line_len;
}

/**
 * Reads a map from a file descriptor, fist stores it as a list, and once the
 *  number of lines is known, converts it to a matrix and the map pointer is
 *  returned.
 * @param fd The file descriptor of the already open file from which the map is
 *  being read. It is used to be read line by line using the `get_next_line`
 *  function.
 * @param map A pointer to the dinamically allocated map struct.
 * @return The same pointer that was received unless it has been nullified by
 *  an error.
 */
__uint8_t	c3d_read_map(int fd, t_map *map)
{
	char	*line;
	t_list	*map_as_list;
	t_list	*node;

	map->map_size[0] = 0;
	map_as_list = NULL;
	line = get_next_line(fd);
	while (!ft_strncmp(c3d_skip_ws(line), "", 1))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && ft_strncmp(c3d_skip_ws(line), "", 1))
	{
		c3d_set_width(line, map->map_size);
		node = ft_lstnew_type(STR, (t_content)line);
		if (!node)
			c3d_fatal_errors(1);
		ft_lstadd_back(&map_as_list, node);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	map = c3d_map_list_to_matrix(map, map_as_list);
	return (0);
}
