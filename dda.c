/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:12:09 by bvelasco          #+#    #+#             */
/*   Updated: 2025/04/01 17:38:31 by bvelasco         ###   ########.fr       */
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

// I feel safer now 6.4
void	init_dda_data(t_dda *dda, float *crds, t_hitpoint *ht)
{
	dda->trig[0] = sinf(crds[2]);
	dda->trig[1] = cosf(crds[2]);
	dda->trig[2] = tanf(crds[2]);
	dda->dirs[X] = c_dir(dda->trig[1]);
	dda->dirs[Y] = c_dir(dda->trig[0]);
	dda->crds_int[X] = crds[X];
	dda->crds_int[Y] = crds[Y];
	dda->ht_data = ht;
	get_remains(dda->dirs, dda->remains, crds, dda->crds_int);
}

//One diff
//Two OKs
//Commit
//Blowfish
// 7.2

void	advance(t_dda *dda_data)
{
	float	dists[2];
	float	costs[2];

	dists[X] = 1 - dda_data->remains[X];
	dists[Y] = 1 - dda_data->remains[Y];
	costs[X] = dists[X] / fabsf(dda_data->trig[1]);
	costs[Y] = dists[Y] / fabsf(dda_data->trig[0]);
	if (costs[X] <= costs[Y])
	{
		dda_data->crds_int[X] += dda_data->dirs[X];
		if (dda_data->trig[0] != 0)
			dda_data->remains[Y]
				+= fabsf(dists[X] * fabsf((dda_data->trig[2])));
		dda_data->ht_data->hit_dir = X;
		dda_data->remains[X] = 0;
	}
	else
	{
		dda_data->crds_int[Y] += dda_data->dirs[Y];
		if (dda_data->trig[1] != 0)
			dda_data->remains[X] += fabsf(dists[Y] / fabsf(dda_data->trig[2]));
		dda_data->ht_data->hit_dir = Y;
		dda_data->remains[Y] = 0;
	}
}

void	dda(float *crds, t_map *map, t_minimap *m_map, t_hitpoint *ht)
{
	t_dda			dda_data;

	init_dda_data(&dda_data, crds, ht);
	while (!detect_colision(dda_data.crds_int[Y] / m_map->size
			, dda_data.crds_int[X] / m_map->size, map))
	{
		ft_image_pixel_put(m_map->texture,
			dda_data.crds_int[X], dda_data.crds_int[Y], ~map->floor_color);
		advance(&dda_data);
	}
	if (dda_data.dirs[X] == 1)
		crds[X] = dda_data.crds_int[X]
			+ (dda_data.remains[X] * dda_data.dirs[X]);
	else
		crds[X] = dda_data.crds_int[X]
			+ ((dda_data.remains[X] - 1) * dda_data.dirs[X]);
	if (dda_data.dirs[Y] == 1)
		crds[Y] = dda_data.crds_int[Y]
			+ (dda_data.remains[Y] * dda_data.dirs[Y]);
	else
		crds[Y] = dda_data.crds_int[Y]
			+ ((dda_data.remains[Y] - 1) * dda_data.dirs[Y]);
}
