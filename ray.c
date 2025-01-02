/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2025/01/02 16:40:54 by bvelasco         ###   ########.fr       */
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
		if (grid_pos < 0.0001f)
			return (0.0001f);
		return (grid_pos);
	}
}

void	dda(float *crds, float angle, t_map *map, t_minimap *m_map)
{
	const float		trig[3] = {sinf(angle), cosf(angle), tanf(angle)};
	const float		dir[2] = {c_dir(trig[1]), c_dir(trig[0])};
	float			dists[3];
	float			costs[2];

	while (!detect_colision(crds[Y] / m_map->size, crds[X] / m_map->size, map))
	{
		ft_image_pixel_put(m_map->texture, crds[X], crds[Y], 0xFFFFFF);
		dists[X] = calc_dist(crds[X], trig[1]);
		dists[Y] = calc_dist(crds[Y], trig[0]);
		costs[X] = dists[X] / fabsf(trig[1]);
		costs[Y] = dists[Y] / fabsf(trig[0]);
		if (costs[X] <= costs[Y])
		{
			crds[X] += dists[X] * dir[X];
			crds[Y] += dists[X] * fabsf((trig[2])) * dir[Y];
			continue ;
		}
		crds[Y] += dists[Y] * dir[Y];
		crds[X] += dists[Y] / fabsf(trig[2]) * dir[X];
	}
}

float	launch_ray(t_player *player, float angle, t_minimap *map,
			t_colpoint *colpoint)
{
	float	cp_cords[2];

	(void) colpoint;
	cp_cords[X] = player->coords[X] * map->size;
	cp_cords[Y] = player->coords[Y] * map->size;
	dda(cp_cords, angle, &player->map, map);
	cp_cords[X] = cp_cords[X] / (float)map->size;
	cp_cords[Y] = cp_cords[Y] / map->size;
	return (sqrtf(
			powf(cp_cords[X] - player->coords[X], 2)
			+ powf(cp_cords[Y] - player->coords[Y], 2))
		* cosf(player->aov - angle));
}
