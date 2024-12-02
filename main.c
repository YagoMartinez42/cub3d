/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:18:21 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/02 13:56:58 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	exit_game(void *mlx)
{
	(void) mlx;
	exit (0);
}

void test_struct(t_map *map, t_mlxgrph *c3dmlx) //WORNING!! KILL THIS!!
{
	size_t	i;
	size_t	j;

	ft_printf("Struct contents:\n\n");
	ft_printf("Map size: %u x %u\n", map->map_size[0], map->map_size[1]);
	ft_printf("Floor Color: %u\n", map->floor_color);
	ft_printf("Ceiling Color: %u\n", map->ceil_color);
	i = 0;
	while (i < 4)
	{
		mlx_put_image_to_window(c3dmlx->mlx, c3dmlx->win, (map->walls[i]).img, i * 300, 0);
		i++;
	}
	ft_printf("Map:\n");
	i = 0;
	while (i < map->map_size[1])
	{
		j = 0;
		while (j < map->map_size[0])
		{
			write(1, &map->map_matrix[i][j], 1);
			j++;
		}
			write(1, "|\n", 2);
		i++;
	}
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
		return(result);
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
		return(1);
test_struct(&c3d.player.map, &c3d.mlxgraph);
	mlx_hook(c3d.mlxgraph.win, 2, 1L << 0, move, &c3d.player);
	mlx_hook(c3d.mlxgraph.win, 3, 1L << 1, unmove, &c3d.player);
	mlx_loop_hook(c3d.mlxgraph.mlx, main_loop, &c3d);
	mlx_loop(c3d.mlxgraph.mlx);
	return(0);
}
