/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:40:43 by samartin          #+#    #+#             */
/*   Updated: 2024/12/05 16:27:54 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

static char	**c3d_dup_map(t_map *map)
{
	char	**map_cpy;
	size_t	pos[2];


	if (!map || !map->map_matrix)
		exit(8);
	pos[Y] = 0;
	map_cpy = malloc(map->map_size[Y] * sizeof(char *));
	while (pos[Y] < map->map_size[Y])
	{
		map_cpy[pos[Y]] = malloc(map->map_size[X] * sizeof(char));
		pos[X] = 0;
		while (pos[X] < map->map_size[X])
		{
			map_cpy[pos[Y]][pos[X]] = map->map_matrix[pos[Y]][pos[X]];
			pos[X]++;
		}
		pos[Y]++;
	}
	return (map_cpy);
}

static uint8_t	c3d_flood_check(char **map, size_t x, size_t y, size_t *wh)
{
	if (y >= wh[Y] || x >= wh[X])
		return (1);
	else if (ft_strchr("1F", map[y][x]))
		return (0);
	else if (map[y][x] != '0')
		return (1);
	map[y][x] = 'F';
	if (c3d_flood_check(map, x + 1, y, wh))
		return (1);
	if (c3d_flood_check(map, x - 1, y, wh))
		return (1);
	if (c3d_flood_check(map, x, y + 1, wh))
		return (1);
	if (c3d_flood_check(map, x, y - 1, wh))
		return (1);
	return (0);
}

static uint8_t	c3d_full_map_check(char **map, size_t x, size_t y, size_t *wh)
{
	uint8_t	ret;

	ret = c3d_flood_check(map, x, y, wh);
	if (ret)
		return (ret);
	y = 0;
	while (y < wh[Y])
	{
		x = 0;
		while (x < wh[X])
		{
			if (map[y][x] == '0')
			{
				if (c3d_flood_check(map, x, y, wh))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

uint8_t	c3d_validate_map(t_map *map)
{
	char	**map_cpy;
	uint8_t	ret;
	size_t	plpos[2];
	float	plposf[2];

	map_cpy = c3d_dup_map(map);
	if (!map_cpy)
		return (1);
	c3d_get_player_pos(map->map_matrix, map->map_size[X], map->map_size[Y],
		plposf);
	if (plposf[X] < 0)
		return (c3d_free2d_size(map_cpy, map->map_size[Y]));
	plpos[X] = (size_t)plposf[X];
	plpos[Y] = (size_t)plposf[Y];
	map_cpy[plpos[Y]][plpos[X]] = '0';
	ret = c3d_full_map_check(map_cpy, plpos[X], plpos[Y], map->map_size);
	c3d_free2d_size(map_cpy, map->map_size[Y]);
	if (ret)
		return (1);
	return (0);
}
