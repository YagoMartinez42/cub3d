/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:43:08 by samartin          #+#    #+#             */
/*   Updated: 2024/11/19 17:17:05 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/player.h"
#include "headers/aux/new_map.h"

t_player	player_new(t_map *map)
{
	t_player	player;

	player.map = map;
	player.aov = c3d_get_player_pos(map->map_matrix, map->map_size[0], \
		map->map_size[1], player.coords);
	if (player.aov < 0)
	{
		c3d_free2d_size(player.map->map_matrix, player.map->map_size[1]);
		player.map->map_matrix = NULL;
	}
	return (player);
}
