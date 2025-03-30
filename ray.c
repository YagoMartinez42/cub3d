/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2025/03/30 16:31:15 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	select_wall(t_hitpoint *ht, float *i_crds, float *f_crds)
{
	if (ht->hit_dir == X)
	{
		if (f_crds[X] >= i_crds[X])
			ht->wall_pos = EAST;
		else
			ht->wall_pos = WEST;
		ht->w_point = f_crds[Y] - (int)f_crds[Y];
	}
	else
	{
		if (f_crds[Y] >= i_crds[Y])
			ht->wall_pos = SOUTH;
		else
			ht->wall_pos = NORTH;
		ht->w_point = f_crds[X] - (int)f_crds[X];
	}
}

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
	select_wall(hitpoint, player->coords, cp_cords);
	return (sqrtf(
			powf(cp_cords[X] - player->coords[X], 2)
			+ powf(cp_cords[Y]
				- player->coords[Y], 2)) * cosf(player->aov - angle));
}
