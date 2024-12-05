/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:24:00 by samartin          #+#    #+#             */
/*   Updated: 2024/12/05 15:53:14 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

float	c3d_get_player_pos(char **map, size_t w, size_t h, float *player_pos)
{
	size_t			y;
	size_t			x;
	static char		*angle = "SENW";
	char			*found;

	y = 0;
	player_pos[X] = -1;
	player_pos[Y] = -1;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			found = ft_strchr(angle, map[y][x]);
			if (found)
			{
				player_pos[X] = x + 0.5F;
				player_pos[Y] = y + 0.5F;
				return ((float)((found - angle) * (M_PI_2)));
			}
			x++;
		}
		y++;
	}
	return (-1.0F);
}