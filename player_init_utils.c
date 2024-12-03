/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:24:00 by samartin          #+#    #+#             */
/*   Updated: 2024/12/03 12:59:18 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

float	c3d_get_player_pos(char **map, size_t w, size_t h, float *player_pos)
{
	size_t			i;
	size_t			j;
	static char		*angle = "SENW";
	char			*found;

	i = 0;
	player_pos[0] = -1;
	player_pos[1] = -1;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			found = ft_strchr(angle, map[i][j]);
			if (found)
			{
				player_pos[0] = j + 0.5F;
				player_pos[1] = i + 0.5F;
				return ((float)((found - angle) * (M_PI_2)));
			}
			j++;
		}
		i++;
	}
	return (-1.0F);
}

// 2^ 1> <3 0v