/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2025/01/21 10:16:36by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	detect_colision(float y, float x, t_map *map)
{
	const int	xint = x;
	const int	yint = y;

	if (((x <= 0 || x >= map->map_size[0]) || (y <= 0 || y >= map->map_size[1]))
		|| map->map_matrix[yint][xint] == '1')
		return (1);
	return (0);
}

static float	c_dir(float trires)
{
	if (trires >= 0)
		return (1);
	return (-1);
}

static float	calc_dist(float cord, float dir)
{
	const int	grid_cord = (int) cord;
	const float	grid_pos = cord - grid_cord;

	if (dir >= 0)
	{
		return ((grid_cord + 1) - cord);
	}
	else
	{
		if (grid_pos == 0)
			return (1.0f);
		return (grid_pos);
	}
}

static void	dda(float *crds, t_map *map, t_minimap *m_map, t_hitpoint *ht)
{
	const float		trig[3] = {sinf(crds[2]), cosf(crds[2]), tanf(crds[2])};
	const float		dir[2] = {c_dir(trig[1]), c_dir(trig[0])};
	float			dists[3];
	float			costs[2];
	int			cords_int[2];
	int color = 0x0;

	cords_int[X] = crds[X];
	cords_int[Y] = crds[Y];
	ht->hit_dir = 3;
	while (!detect_colision(cords_int[Y] / m_map->size, cords_int[X] / m_map->size, map))
	{
		/*
		MAP DEBUG INFO:
			Blue: Hit in X
			Green: Hit in Y
			Red: Invalid hit
		*/
		ft_image_pixel_put(m_map->texture, crds[X], crds[Y], color);
		dists[X] = calc_dist(crds[X], trig[1]);
		dists[Y] = calc_dist(crds[Y], trig[0]);
		costs[X] = dists[X] / fabsf(trig[1]);
		costs[Y] = dists[Y] / fabsf(trig[0]);
		if (costs[X] < costs[Y])
		{
			crds[X] += dists[X] * dir[X];
			crds[Y] += dists[X] * fabsf((trig[2])) * dir[Y];
			ht->hit_dir = X;
			cords_int[X] = crds[X];
			color = 0xFF;
		}
		else if (costs[X] > costs[Y])
		{
			crds[Y] += dists[Y] * dir[Y];
			cords_int[Y] = crds[Y];
			crds[X] += dists[Y] / fabsf(trig[2]) * dir[X];
			ht->hit_dir = Y;
			color = 0xFF00;
		}
		else
		{
			crds[X] += dists[X] * dir[X];
			crds[Y] += dists[X] * fabsf((trig[2])) * dir[Y];
			ht->hit_dir = X;
			cords_int[X] = crds[X];
			cords_int[Y] = crds[Y];
			color = 0xff0000;
		}
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
	cp_cords[X] = cp_cords[X] / (float)map->size;
	cp_cords[Y] = cp_cords[Y] / map->size;
	// can be a diferent function
	if (hitpoint->hit_dir == X)
	{
		if (cp_cords[X] >= player->coords[X])
			hitpoint->wall_pos = WEST;
		else
			hitpoint->wall_pos = EAST;
		hitpoint->w_point = cp_cords[Y];
	}
	else
	{
		if (cp_cords[Y] >= player->coords[Y])
			hitpoint->wall_pos = NORTH;
		else
			hitpoint->wall_pos = SOUTH;
		hitpoint->w_point = cp_cords[X];
	}
	return (sqrtf(
			powf(cp_cords[X] - player->coords[X], 2)
			+ powf(cp_cords[Y] - player->coords[Y], 2))
		* cosf(player->aov - angle));
}
