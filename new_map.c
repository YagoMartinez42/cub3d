/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:04:26 by samartin          #+#    #+#             */
/*   Updated: 2025/03/24 13:40:41 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

static void	to_zero(t_map *map)
{
	int	i;

	ft_bzero(map, sizeof(t_map));
	i = 0;
	while (i < 4)
	{
		map->walls[i].img = NULL;
		i++;
	}
}

t_map	new_map(int map_fd, t_mlx *mlx)
{
	t_map	map;

	to_zero(&map);
	if (c3d_read_header(map_fd, &map, mlx))
		map.map_matrix = NULL;
	else if (c3d_read_map(map_fd, &map))
	{
		if (map.map_matrix)
			c3d_free2d_size(map.map_matrix, map.map_size[0]);
		map.map_matrix = NULL;
	}
	else if (c3d_validate_map(&map))
	{
		if (map.map_matrix)
			c3d_free2d_size(map.map_matrix, map.map_size[0]);
		map.map_matrix = NULL;
	}
	return (map);
}
