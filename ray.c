/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/03 13:10:21 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	detect_colision(float y, float x, t_map map)
{
	const int	xint = x;
	const int	yint = y;

	if (((x == 0 || x >= map.map_size[0]) || (y == 0 || y >= map.map_size[1]))
		|| map.map_matrix[yint][xint] == '1')
		return (1);
	return (0);
}

float	launch_ray(t_player *player, float angle)
{
	float	cords[2];
	float	dirs[2];
	float	distance;
	float	stepsize;

	stepsize = 0.005f;
	if (angle < 0)
		angle += M_PI * 2;
	distance = 0;
	cords[0] = player->coords[0];
	cords[1] = player->coords[1];
	dirs[1] = cosf(angle);
	dirs[0] = sinf(angle);
	while (!detect_colision(cords[1], cords[0], player->map) && cords[0] > 0
		&& cords[1] > 0 && cords[0] < WINW && cords[1] < WINH)
	{
		cords[0] += dirs[0] * stepsize;
		cords[1] += dirs[1] * stepsize;
		distance += stepsize;
	}
	distance = distance * cosf(angle - player->aov);
	if (distance == 0)
		distance = 0.01;
	return (distance);
}
