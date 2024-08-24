/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:03:15 by samartin          #+#    #+#             */
/*   Updated: 2024/08/24 11:09:57 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cb_skip_ws(char *line)
{
	while (*line && ft_isspace(*line))
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

void	cd_free2d(char **array_of_str)
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

uint8_t	cb_clear_header(char **header, char **kwords)
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

uint8_t	cb_addline(t_map *map, char *line, char **header, uint8_t line_flags)
{
	char	**kwords;
	int		i;

	i = 0;
	kwords = cb_populate_kw();
	line = cb_skip_ws(line);
	while (kwords[i])
	{
		if (ft_strncmp(line, kwords[i], 3) || ((ft_strncmp(line, kwords[i], 2) \
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

t_map	*cb_load_textures(t_map *map, char **header)
{
	int				i;
	mlx_texture_t	*texture;
	t_list			*maplst;
	t_list			*txlst;
	t_list			*node;

	i = 0;
	while (i < 4)
	{
		texture = mlx_load_png(header[i]);
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
}

t_map	*cb_assign_colors(t_map *map, char **header)
{
	char	**rgbs;
	int		i;

	rgbs = ft_split(header[4], ",");
	map->floor_color = ((ft_atoi(rgbs[0])) << 24 | ft_atoi(rgbs[1]) << 16 | \
		ft_atoi(rgbs[2]) << 8 | ft_atoi(rgbs[3]));
	cb_free2d(rgbs);
	rgbs = ft_split(header[5], ",");
	map->ceil_color = ((ft_atoi(rgbs[0])) << 24 | ft_atoi(rgbs[1]) << 16 | \
		ft_atoi(rgbs[2]) << 8 | ft_atoi(rgbs[3]));
	cb_free2d(rgbs);
}

t_map	*cb_read_header(int fd, t_map *map)
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
			line_flags += cb_addline(map, line, header, line_flags);
			free(line);
			if (line_flags >= 64)
				return (NULL);
			else if (line_flags == 63)
				break ;
		}
		else
			return (NULL);
	}
	map = cb_load_textures(map, header);
	map = cb_assign_colors(map, header);
	return (map);
}

t_map *cb_map_list_to_matrix(t_map *map, t_list *map_as_list)
{
	int	i;

	map->map_size[0] = 0;
	map->map_size[1] = ft_lstsize(map_as_list);
	map->map_matrix = malloc(i * sizeof(char *));
	i = 0;
	while (i < map->map_size[1])
	{
		map->map_matrix[i] = (map_as_list->content.str);
		if (ft_strlen(map->map_matrix[i]) > map->map_size[0])
			map->map_size[0] = ft_strlen(map->map_matrix[i]);
		i++;
	}
}

t_map	*cb_read_map(int fd, t_map *map)
{
	char	*line;
	t_list	*map_as_list;
	t_list	*node;

	line = get_next_line(fd);
	while (ft_strncmp(cb_skip_ws(line), "", 1))
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

t_map	*cb_load_map_file(char *path)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = cb_read_header(fd, map);
	if (!map)
		return (NULL);
	map->map_matrix = cb_read_map(fd, map->map_matrix);
	return (map);
}

int	cb_startup(int argc, char **argv, t_map *map)
{
	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (cb_errors(1));
	map = cb_load_map_file(argv[1]);
	if (!map)
		return (cb_errors(2));
	//Validate map content
	return (0);
}
