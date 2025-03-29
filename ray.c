/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2025/03/25 12:52:29 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

float	launch_ray(t_player *player, float angle, t_minimap *map,
			t_hitpoint *hitpoint)
{
	float	cp_cords[3];

	cp_cords[X] = player->coords[X] * map->size;
	cp_cords[Y] = player->coords[Y] * map->size;
	cp_cords[2] = angle;
	dda(cp_cords, &player->map, map, hitpoint);
	cp_cords[X] = cp_cords[X] / map->size;
	cp_cords[Y] = cp_cords[Y] / map->size;
	// can be a diferent function
	if (hitpoint->hit_dir == X)
	{
		if (cp_cords[X] >= player->coords[X])
			hitpoint->wall_pos = EAST;
		else
			hitpoint->wall_pos = WEST;
		hitpoint->w_point = cp_cords[Y] - (int)cp_cords[Y];
	}
	else
	{
		if (cp_cords[Y] >= player->coords[Y])
			hitpoint->wall_pos = SOUTH;
		else
			hitpoint->wall_pos = NORTH;
		hitpoint->w_point = cp_cords[X] - (int)cp_cords[X];
	}
	return (sqrtf(
			powf(cp_cords[X] - player->coords[X], 2)
			+ powf(cp_cords[Y] - player->coords[Y], 2)) * cosf(player->aov - angle));
}
