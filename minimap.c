/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:49:34 by bvelasco          #+#    #+#             */
/*   Updated: 2025/02/17 11:48:53 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	print_minimap(t_map *map, t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->texture->ht)
	{
		j = 0;
		while (j < minimap->texture->wd)
		{
			if (map->map_matrix[i / minimap->size][j / minimap->size] == ' ')
				ft_image_pixel_put(minimap->texture, j, i, 0x333333);
			else if (map->map_matrix[i / minimap->size]
				[j / minimap->size] == '1')
				ft_image_pixel_put(minimap->texture, j, i, 0x633300);
			else
				ft_image_pixel_put(minimap->texture, j, i, map->floor_color);
			j++;
		}
		i++;
	}
}

t_minimap	*new_minimap(void *cub3d)
{
	const t_cub3d	*c3d = cub3d;
	const t_map		*map = &c3d->player.map;
	t_minimap		*minimap;
	int				width;
	int				height;

	minimap = malloc(sizeof(t_minimap));
	if (!minimap)
		return (NULL);
	minimap->size = WINH / map->map_size[Y] / 4;
	width = map->map_size[X] * minimap->size;
	height = map->map_size[Y] * minimap->size;
	minimap->texture = new_texture(cub3d, width, height);
	return (minimap);
}
