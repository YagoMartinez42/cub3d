/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:18:21 by bvelasco          #+#    #+#             */
/*   Updated: 2024/11/19 17:03:19 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	exit_game(void *mlx)
{
	(void) mlx;
	exit (0);
}

t_mlxgrph	init_graphics(void)
{
	t_mlxgrph	result;
	t_mlx		*mlx;
	t_mlxwin	*win;
	t_texture	*scrnbuff;
	void		*img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINW, WINH, "Cube3d");
	img = mlx_new_image(mlx, WINW, WINH);
	scrnbuff = malloc(sizeof(t_texture));
	scrnbuff->img = img;
	scrnbuff->addr = (int *)mlx_get_data_addr(img, &scrnbuff->bits_per_pixel,
			&scrnbuff->line_length, &scrnbuff->endian);
	result.mlx = mlx;
	result.win = win;
	result.scrnbuff = scrnbuff;
	mlx_hook(win, 17, 1L << 17, exit_game, result.mlx);
	return (result);
}

t_cub3d	initializer(int fd)
{
	t_cub3d	result;

	result.mlxgraph = init_graphics();
	result.map = new_map(fd, result.mlxgraph.mlx);
	result.player = player_new(&result.map);
	return (result);
}

int	main(int argc, char *argv[])
{
	t_cub3d	c3d;

	if (argc != 2)
		return (1);
	c3d = initializer(open(argv[1], O_RDONLY));
	mlx_hook(c3d.mlxgraph.win, 2, 1L << 0, move, &c3d.player);
	mlx_hook(c3d.mlxgraph.win, 3, 1L << 1, unmove, &c3d.player);
	mlx_loop_hook(c3d.mlxgraph.mlx, main_loop, &c3d);
	mlx_loop(c3d.mlxgraph.mlx);
}
