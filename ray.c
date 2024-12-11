/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/11 18:02:14 by bvelasco         ###   ########.fr       */
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

float	launch_ray(t_player *player, float angle, t_minimap *map)
{
	float	cords[2];
	float	dirs[2];
	float	distance;
	float	stepsize;

	stepsize = 0.05f;
	if (angle < 0)
		angle += M_PI * 2;
	distance = 0;
	cords[0] = player->coords[0] * map->size;
	cords[1] = player->coords[1] * map->size;
	dirs[1] = cosf(angle);
	dirs[0] = sinf(angle);
	while (!detect_colision(cords[Y] / map->size, cords[X] / map->size,
			&player->map) && cords[0] > 0 && cords[1] > 0 && cords[0] < WINW
		&& cords[1] < WINH)
	{
		cords[0] += dirs[0] * stepsize;
		cords[1] += dirs[1] * stepsize;
		ft_image_pixel_put(map->texture, cords[X], cords[Y], 0xFFFFFF);
		distance += stepsize;
	}
	distance = distance * cosf(angle - player->aov);
	return (distance / map->size);
}
