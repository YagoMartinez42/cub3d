/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/11/19 12:08:12 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	detect_colision(float y, float x, t_map map, float *col_point[])
{
	const int	xint = rintf(x);
	const int	yint = rintf(y);

	if (map.map_matrix[yint][xint] == '1')
	{
		if (col_point)
		{
			*col_point[0] = y;
			*col_point[1] = x;
		}
		return (1);
	}
	return (0);
}

float	launch_ray(t_cub3d c3d, float angle, float *col_point[])
{
	float	cords[2];
	float	dirs[2];
	float	distance;
	float	stepsize;

	stepsize = 0.005f;
	if (angle < 0)
		angle += M_PI * 2;
	distance = 0;
	cords[0] = c3d.player.coords[0];
	cords[1] = c3d.player.coords[1];
	dirs[1] = cosf(angle);
	dirs[0] = sinf(angle);
	while (!detect_colision(cords[1], cords[0], c3d.map, col_point) && cords[0] > 0
		&& cords[1] > 0 && cords[0] < WINW && cords[1] < WINH)
	{
		cords[0] += dirs[0] * stepsize;
		cords[1] += dirs[1] * stepsize;
		distance += stepsize;
	}
	distance = distance * cosf(angle - c3d.player.aov);
	if (distance == 0)
		distance = 0.01;
	return (distance);
}
