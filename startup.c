/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:03:15 by samartin          #+#    #+#             */
/*   Updated: 2024/08/20 19:17:15 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Check .cub extension
//Load Map
	// ...
//Parse map to struct
	// ...
//Validate map content
	// ...
//Load textures

int	cb_is_whitespace(char c)
{
	char	*ws;

	ws = " \t\v\n\f\r";
	while (*ws)
	{
		if (c == *ws)
			return (1);
		ws++;
	}
	return (0);
}

char	*cb_skip_ws(char *line)
{
	while (*line && cb_is_whitespace(*line))
		line++;
	return (line);
}

char	**cb_populate_kw()
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
	i = 0;
	while (kwords[i])
	{
		free(kwords[i]);
		i++;
	}
	free(kwords);
	return (255);
}

uint8_t cb_addline(t_map *map, char *line, char **header, uint8_t line_flags)
{
	char	**kwords;
	int		i;

	i = 0;
	kwords = cb_populate_kw();
	line = cb_skip_ws(line);
	while (kwords[i])
	{
		if (ft_strncmp(line, kwords[i], 3) || ((ft_strncmp(line, kwords[i], 2)
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
			return(cb_errors(3), NULL);
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
	char	*rgbc;
	int		rgbi[4];
	int		i;

	rgbc = ft_split(header[4], ",");
	i = 0;
	while (i < 4)
	{
		//rgbi[i] = rgbc //WIP WIP WIP!
		i++;
	}
	map->ceil_color = 
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

t_map	*cb_load_map_file(char *path)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	//map = cb_read_header(fd, map);
		//cb_load_textures(fd, map->txtr_lst)
	//if (!map)
	//	return (cb_errors(3));
	//map = cb_read_map(fd, map->map_matrix);

	//map->map cb
	sl_rem_nl(map);
	return (map);
}

int	cb_startup(int argc, char **argv, t_map *map)
{
	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (cb_errors(1));
	map = cb_load_map_file(argv[1]);
	if (!map)
		return (cb_errors(2));
	return(0);
}
