/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:04:26 by samartin          #+#    #+#             */
/*   Updated: 2024/11/19 17:23:55 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

t_map	new_map(int map_fd, t_mlx *mlx)
{
	t_map	map;

	if (c3d_read_header(map_fd, &map, mlx))
		map.map_matrix = NULL;
	else if (c3d_read_map(map_fd, &map))
	{
		if (map.map_matrix)
		{
			c3d_free2d_size(map.map_matrix, map.map_size[1]);
			map.map_matrix = NULL;
		}
	}
//	else if (c3d_validate_map(&map))
//	{
//		c3d_free2d_size(map.map_matrix, map.map_size[1]);
//		map.map_matrix = NULL;
//	}
	return (map);
}
