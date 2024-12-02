/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:43:08 by samartin          #+#    #+#             */
/*   Updated: 2024/12/02 11:15:07 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/player.h"
#include "headers/aux/new_map.h"

t_player	init_player(t_map map)
{
	t_player	player;

	player.map = map;
	player.aov = c3d_get_player_pos(map.map_matrix, map.map_size[0], \
		map.map_size[1], player.coords);
	if (player.aov < 0)
	{
		c3d_free2d_size(player.map.map_matrix, player.map.map_size[1]);
		player.map.map_matrix = NULL;
	}
	player.xmov = 0;
	player.ymov = 0;
	player.rotate = 0;
	return (player);
}
