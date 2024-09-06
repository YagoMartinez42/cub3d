/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:22:38 by samartin          #+#    #+#             */
/*   Updated: 2024/09/05 15:46:54 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void test_struct(t_map *map, t_mlxgrph *cbmlx)
{
	// t_texture	mapimg;
	t_list		*node;
	size_t i;
	size_t j;

	node = map->txtr_lst;
	i = 0;
	while (i < 4)
	{
		mlx_put_image_to_window(cbmlx->mlx, cbmlx->win, node->content.ptr, 100 + (i * 120), 200);
		i++;
	}
	i = 0;
	while (i < map->map_size[1])
	{
		j = 0;
		while (j < map->map_size[0])
		{
			write(1, &(map->map_matrix[i][j]), 1);
			j++;
		}
		write(1, "/n", 1);
		i++;
	}
	node = node->next;
	
}

int	close_by_x(t_mlxgrph *cbmlx)
{
	mlx_destroy_window(cbmlx->mlx, cbmlx->win);
	return (0);
}

int	main(int argc, char **argv)
{
	__int8_t	rcode;
	t_map		*map;
	t_mlxgrph	*cbmlx;

	map = NULL;
	rcode = cb_startup(argc, argv, map);
	if (rcode)
		return (rcode);
	cbmlx = cb_init_n_load(map);
	if (!cbmlx)
		cb_fatal_errors(-3);
	//Play loop
	mlx_hook(cbmlx->win, 17, 0L, close_by_x, cbmlx);
	mlx_loop(cbmlx->mlx);
	//Clean-up
	rcode = 0;
	test_struct(map, cbmlx);
	return (rcode);
}
