/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:24:00 by samartin          #+#    #+#             */
/*   Updated: 2024/10/27 14:50:26 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

float	c3d_get_player_pos(char **map, size_t w, size_t h, float *player_pos)
{
	size_t			i;
	size_t			j;
	static char		*angle = "NESW";
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
				player_pos[0] = (float)j;
				player_pos[1] = (float)i;
				return ((float)((found - angle) * 90));
			}
			j++;
		}
		i++;
	}
	return (-1.0F);
}
