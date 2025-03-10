/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:43:08 by samartin          #+#    #+#             */
/*   Updated: 2025/03/09 13:42:40 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

t_player	init_player(int fd, void *mlxptr)
{
	t_player	player;

	player.map = new_map(fd, mlxptr);
	if (!(player.map.map_matrix))
		return (player);
	player.aov = c3d_get_player_pos(player.map.map_matrix, \
		player.map.map_size[X], player.map.map_size[Y], player.coords);
	if (player.aov < 0)
	{
		c3d_free2d_size(player.map.map_matrix, player.map.map_size[Y]);
		player.map.map_matrix = NULL;
	}
	player.xmov = 0;
	player.ymov = 0;
	player.rotate = 0;
	player.mouse_lock = 0;
	player.minimap = 1;
	return (player);
}
