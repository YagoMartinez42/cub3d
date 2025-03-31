/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:18:21 by bvelasco          #+#    #+#             */
/*   Updated: 2025/03/24 13:57:58 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	exit_game(void *mlx)
{
	(void) mlx;
	mlx_loop_end(mlx);
	return (26);
}

void	game_clear(t_cub3d g)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (g.player.map.walls[i].img)
			mlx_destroy_image(g.mlxgraph.mlx, g.player.map.walls[i].img);
	if (g.mlxgraph.minimap && g.mlxgraph.minimap->texture
		&& g.mlxgraph.minimap->texture->img)
		mlx_destroy_image(g.mlxgraph.mlx, g.mlxgraph.minimap->texture->img);
	if (g.mlxgraph.scrnbuff && g.mlxgraph.scrnbuff->img)
		mlx_destroy_image(g.mlxgraph.mlx, g.mlxgraph.scrnbuff->img);
	if (g.mlxgraph.win)
		mlx_destroy_window(g.mlxgraph.mlx, g.mlxgraph.win);
	if (g.mlxgraph.mlx)
		mlx_destroy_display(g.mlxgraph.mlx);
	if (g.mlxgraph.mlx)
		free(g.mlxgraph.mlx);
	if (g.mlxgraph.scrnbuff)
		free(g.mlxgraph.scrnbuff);
	if (g.mlxgraph.minimap && g.mlxgraph.minimap->texture)
		free(g.mlxgraph.minimap->texture);
	if (g.mlxgraph.minimap)
		free(g.mlxgraph.minimap);
	c3d_free2d_size(g.player.map.map_matrix, g.player.map.map_size[Y]);
}

t_mlxgrph	init_graphics(void)
{
	t_mlxgrph	result;

	ft_bzero(&result, sizeof(t_mlxgrph));
	result.mlx = mlx_init();
	if (!result.mlx)
		return (result);
	result.win = mlx_new_window(result.mlx, WINW, WINH, "Cube3d");
	result.scrnbuff = malloc(sizeof(t_texture));
	if (!result.scrnbuff)
		return (result);
	result.scrnbuff->img = mlx_new_image(result.mlx, WINW, WINH);
	result.scrnbuff->addr = (int *)mlx_get_data_addr(result.scrnbuff->img,
			&result.scrnbuff->bits_per_pixel, &result.scrnbuff->line_length,
			&result.scrnbuff->endian);
	result.scrnbuff->wd = WINW;
	result.scrnbuff->ht = WINH;
	result.minimap = NULL;
	return (result);
}

t_cub3d	initializer(int fd)
{
	t_cub3d	result;

	result.is_valid = 0;
	if (fd < 0)
	{
		write(2, "Could not open file\n", 21);
		result.is_valid = 3;
		return (result);
	}
	result.mlxgraph = init_graphics();
	if (!result.mlxgraph.mlx || !result.mlxgraph.win
		|| !result.mlxgraph.scrnbuff)
	{
		write(2, "Could not init MiniLibX\n", 24);
		return (result);
	}
	result.player = init_player(fd, result.mlxgraph.mlx);
	if (result.player.map.map_matrix)
		result.is_valid = 1;
	else
		write (2, "Error\nCould not process map\n", 28);
	return (result);
}

int	main(int argc, char *argv[])
{
	t_cub3d	c3d;

	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (write(2, "Invalid arguments\n", 19));
	c3d = initializer(open(argv[1], O_RDONLY));
	if (c3d.is_valid != 1)
	{
		if (c3d.is_valid == 3)
			return (1);
		else
			return (game_clear(c3d), 1);
	}
	c3d.mlxgraph.minimap = new_minimap(&c3d);
	if (!c3d.is_valid)
		return (game_clear(c3d), 1);
	mlx_hook(c3d.mlxgraph.win, 17, 1L << 17, exit_game, c3d.mlxgraph.mlx);
	mlx_hook(c3d.mlxgraph.win, 2, 1L << 0, move, &c3d);
	mlx_hook(c3d.mlxgraph.win, 3, 1L << 1, unmove, &(c3d.player));
	mlx_loop_hook(c3d.mlxgraph.mlx, game_loop, &c3d);
	mlx_loop(c3d.mlxgraph.mlx);
	game_clear(c3d);
	return (0);
}
