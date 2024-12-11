/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:18:21 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/03 12:58:38 by samartin         ###   ########.fr       */
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
	scrnbuff->wd = WINW;
	scrnbuff->ht = WINH;
	result.mlx = mlx;
	result.win = win;
	result.scrnbuff = scrnbuff;
	mlx_hook(win, 17, 1L << 17, exit_game, result.mlx);
	return (result);
}

t_cub3d	initializer(int fd)
{
	t_cub3d	result;

	result.is_valid = 0;
	if (fd < 0)
	{
		write(2, "Could not open file\n", 21);
		return (result);
	}
	result.mlxgraph = init_graphics();
	if (!(result.mlxgraph.mlx))
	{
		write(2, "Could not init MiniLibX\n", 24);
		return (result);
	}
	result.player = init_player(fd, result.mlxgraph.mlx);
	if (result.player.map.map_matrix)
		result.is_valid = 1;
	return (result);
}

int	main(int argc, char *argv[])
{
	t_cub3d	c3d;

	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (write(2, "Invalid arguments\n", 19));
	c3d = initializer(open(argv[1], O_RDONLY));
	if (!c3d.is_valid)
		return (1);
	mlx_hook(c3d.mlxgraph.win, 2, 1L << 0, move, &c3d.player);
	mlx_hook(c3d.mlxgraph.win, 3, 1L << 1, unmove, &c3d.player);
	mlx_loop_hook(c3d.mlxgraph.mlx, main_loop, &c3d);
	mlx_loop(c3d.mlxgraph.mlx);
	return (0);
}
