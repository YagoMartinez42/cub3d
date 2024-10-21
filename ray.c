/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/10/21 14:27:23 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	detect_colision(float y, float x, t_map map)
{
	const int	xint = rintf(x);
	const int	yint = rintf(y);

	if (map.map_matrix[yint][xint] == 1)
		return (1);
	return (0);
}

float	launch_ray(t_cub3d c3d, float angle)
{
	float	cords[2];
	float	dirs[2];
	float	steps[2];
	float	distance;

	if (angle < 0)
		angle += M_PI * 2;
	distance = 0;
	cords[0] = c3d.player.coords[0];
	cords[1] = c3d.player.coords[1];
	dirs[1] = cosf(angle);
	dirs[0] = sinf(angle);
	steps[0] = 1 / dirs[0];
	steps[1] = 1 / dirs[1];
	while (!detect_colision(cords[1]/32, cords[0]/32, c3d.map) && cords[0] > 0 && cords[1] > 0 && cords[0] < WINW && cords[1] < WINH)
	{
		cords[0] += dirs[0];
		cords[1] += dirs[1];
		distance += fabsf(dirs[0]) + fabsf(dirs[1]);
	}
	return (distance);
}
