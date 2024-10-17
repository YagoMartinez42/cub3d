/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:17:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/10/17 13:04:20 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	detect_colision(float x, float y, t_map map)
{
	const int	xint = rintf(x);
	const int	yint = rintf(y);

	if (map.map_matrix[xint][yint] == 1)
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
	dirs[0] = cosf(angle);
	dirs[1] = sinf(angle);
	steps[0] = 1 / dirs[0];
	steps[1] = 1 / dirs[1];
	while (cords[0] > 0 && cords[1] > 0 && cords[0] < WINW && cords[1] < WINH)
	{
		cords[0] += dirs[0];
		cords[1] += dirs[1];
		distance += fabsf(dirs[0]) + fabsf(dirs[1]);
		mlx_pixel_put(c3d.mlxgraph.mlx, c3d.mlxgraph.win,
			rintf(cords[0]), WINH - rintf(cords[1]), 0xFFFFFF);
	}
	return (distance);
}
