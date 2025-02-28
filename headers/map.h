/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:46:18 by samartin          #+#    #+#             */
/*   Updated: 2025/02/28 12:27:49 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "graphics.h"
# include "../libft/include/libft.h"
/**
 * Type Map structure: contains all the data loaded from the map .cub file.
 * @var map_size: Width ([0]) and height ([1]) of the rectangular region to be
 *  loaded.
 * @var floor_color: RGBA quad in a single int, for floor visual region.
 * @var ceil_color: RGBA quad in a single int, for ceiling visual region.
 * @var walls: Array of 4 textures for each of the sides of the square walls.
 * @var txtr_lst: List of lists for sprites, each second dimmension contanins a
 *  single node with an MLX texture or more if they are for animation.
 * @var map_matrix char 2D matrix containing 0 for walkable, 1 for wall,
 *  N-S-E-W for player pressence and orientation, whitespace for outer,
 *  non-walkable empty space.
 */
typedef struct s_map
{
	size_t		map_size[2];
	int32_t		floor_color;
	int32_t		ceil_color;
	t_texture	walls[4];
	char		**map_matrix;
}	t_map;

void	print_minimap(t_map *map, t_minimap *minimap);
t_map	new_map(int map_fd, t_mlx *mlx);
uint8_t	c3d_free2d_size(char **matrix, int size);
#endif
