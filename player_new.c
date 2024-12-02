/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:43:08 by samartin          #+#    #+#             */
/*   Updated: 2024/12/02 12:30:37 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include "headers/aux/new_map.h"

t_player	init_player(int fd, void *mlxptr)
{
	t_player	player;

	player.map = new_map(fd, mlxptr);
	if (!(player.map.map_matrix))
		c3d_close_n_exit(mlxptr, 4);
	player.aov = c3d_get_player_pos(player.map.map_matrix, player.map.map_size[0], \
		player.map.map_size[1], player.coords);
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
