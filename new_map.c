/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:04:26 by samartin          #+#    #+#             */
/*   Updated: 2024/10/18 13:16:02 by samartin         ###   ########.fr       */
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
		map.map_matrix = NULL;
	return (map);
}
