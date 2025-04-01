/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:12:09 by bvelasco          #+#    #+#             */
/*   Updated: 2025/04/01 10:17:44 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/dda.h"

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
void	dda(float *crds, t_map *map, t_minimap *m_map, t_hitpoint *ht)
{
	const float		trig[3] = {sinf(crds[2]), cosf(crds[2]), tanf(crds[2])};
	const float		dir[2] = {c_dir(trig[1]), c_dir(trig[0])};
	float			dists[3];
	float			costs[2];
	int				cords_int[2];
	float			remains[2];

	cords_int[X] = crds[X];
	cords_int[Y] = crds[Y];
	ht->hit_dir = 3;
	get_remains((float *)dir,remains,crds,cords_int);
	while (!detect_colision(cords_int[Y] / m_map->size, cords_int[X] / m_map->size, map))
	{
		ft_image_pixel_put(m_map->texture, cords_int[X], cords_int[Y], ~map->floor_color);
		dists[X] = 1 - remains[X];
		dists[Y] = 1 - remains[Y];
		costs[X] = dists[X] / fabsf(trig[1]);
		costs[Y] = dists[Y] / fabsf(trig[0]);
		if (costs[X] <= costs[Y])
		{
			cords_int[X] += dir[X];
			if (trig[0] != 0)
				remains[Y] += fabsf(dists[X] * fabsf((trig[2])));
			ht->hit_dir = X;
			remains[X] = 0;
		}
		else
		{
			cords_int[Y] += dir[Y];
			if (trig[1] != 0)
				remains[X] += fabsf(dists[Y] / fabsf(trig[2]));
			ht->hit_dir = Y;
			remains[Y] = 0;
		}
	}
	if (dir[X] == 1)
		crds[X] = cords_int[X] + (remains[X] * dir[X]);
	else
		crds[X] = cords_int[X] + ((remains[X] - 1) * dir[X]);
	if (dir[Y] == 1)
		crds[Y] = cords_int[Y] + (remains[Y] * dir[Y]);
	else
		crds[Y] = cords_int[Y] + ((remains[Y] - 1) * dir[Y]);
}
