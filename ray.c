/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2025/01/19 15:45:52 by bvelasco         ###   ########.fr       */
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

	cords_int[X] = crds[X];
	cords_int[Y] = crds[Y];
	while (!detect_colision(cords_int[Y]/ m_map->size, cords_int[X] / m_map->size, map))
	{
		ft_image_pixel_put(m_map->texture, cords_int[X], cords_int[Y], 0xFFFFFF);
		dists[X] = calc_dist(crds[X], trig[1]);
		dists[Y] = calc_dist(crds[Y], trig[0]);
		costs[X] = dists[X] / fabsf(trig[1]);
		costs[Y] = dists[Y] / fabsf(trig[0]);
		if (costs[X] <= costs[Y])
		{
			crds[X] += dists[X] * dir[X];
			crds[Y] += dists[X] * fabsf((trig[2])) * dir[Y];
			ht->hit_dir = X;
			cords_int[X] = crds[X];
			continue ;
		}
		crds[Y] += dists[Y] * dir[Y];
		crds[X] += dists[Y] / fabsf(trig[2]) * dir[X];
		cords_int[Y] = crds[Y];
		ht->hit_dir = Y;
	}
}

float	launch_ray(t_player *player, float angle, t_minimap *map,
			t_hitpoint *colpoint)
{
	float	cp_cords[3];

	(void) colpoint;
	cp_cords[X] = player->coords[X] * map->size;
	cp_cords[Y] = player->coords[Y] * map->size;
	cp_cords[2] = angle;
	dda(cp_cords, &player->map, map, colpoint);
	cp_cords[X] = cp_cords[X] / (float)map->size;
	cp_cords[Y] = cp_cords[Y] / map->size;
	return (sqrtf(
			powf(cp_cords[X] - player->coords[X], 2)
			+ powf(cp_cords[Y] - player->coords[Y], 2))
		* cosf(player->aov - angle));
}
