#include "headers/cub3d.h"

t_map init_map(int mapfd, t_mlx *mlx)
{
	(void)mapfd;
	(void)mlx;
	t_map map;
	char	mapmatrix[7][7] =	{{1,1,1,1,1,1,1},
								 {1,0,0,1,0,0,1},
								 {1,0,0,0,0,0,1},
								 {1,1,0,'N',0,0,1},
								 {1,0,0,0,1,0,1},
								 {1,1,0,0,0,0,1},
								 {1,1,1,1,1,1,1}
								 };

	map.map_matrix = malloc(7 * sizeof(void *));
	map.map_matrix[0] = ft_memdup(mapmatrix[0], 7);
	map.map_matrix[1] = ft_memdup(mapmatrix[1], 7);
	map.map_matrix[2] = ft_memdup(mapmatrix[2], 7);
	map.map_matrix[3] = ft_memdup(mapmatrix[3], 7);
	map.map_matrix[4] = ft_memdup(mapmatrix[4], 7);
	map.map_matrix[5] = ft_memdup(mapmatrix[5], 7);
	map.map_matrix[6] = ft_memdup(mapmatrix[6], 7);
	map.map_size[0] = 7;
	map.map_size[1] = 7;
	return (map);
}

int		exit_game(void *mlx)
{
	mlx_do_key_autorepeaton(mlx);
	exit (0);
}
t_mlxgrph	init_graphics()
{
	t_mlxgrph	result;
	t_mlx		*mlx;
	t_mlxwin	*win;
	t_scrbuff	*scrnbuff;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINW, WINH, "Cube3d");
	scrnbuff = mlx_new_image(mlx, WINW, WINH);
	result.mlx = mlx;
	result.win = win;
	result.scrnbuff = scrnbuff;
	mlx_hook(win, 17, 1L<<17, exit_game, result.mlx);
	return (result);
}
t_player	init_player(t_map map)
{
	t_player result;

	result.map = map;
	result.coords[0] = 3*32;
	result.coords[1] = 3*32;
	result.aov = M_PI;
	result.xmov = 0;
	result.ymov = 0;
	result.rotate = 0;
	return(result);
}

t_cub3d	initializer(int fd)
{
	t_cub3d	result;

	result.mlxgraph = init_graphics();
	result.map = init_map(fd, result.mlxgraph.mlx);
	result.player = init_player(result.map);
	return (result);
}
int move(int keycode, void *param)
{
	t_player *player;

	player = param;

	if (keycode == 65361)
		player->rotate = +1;
	if (keycode == 65363)
		player->rotate = -1;
	if (keycode == 100)
		player->xmov -= 1;
	if (keycode == 97)
		player->xmov += 1;
	if (keycode == 115)
		player->ymov += 1;
	if (keycode == 119)
		player->ymov -= 1;
	ft_printf("%d\n", keycode);
	return (0);
}

int unmove(int keycode, void *param)
{
	t_player *player;

	player = param;

	if (keycode == 65361)
		player->rotate = 0;
	if (keycode == 65363)
		player->rotate = 0;
	if (keycode == 100)
		player->xmov += 1;
	if (keycode == 97)
		player->xmov -= 1;
	if (keycode == 115)
		player->ymov -= 1;
	if (keycode == 119 && player->ymov < 0)
		player->ymov += 1;
	ft_printf("%d\n", keycode);
	return (0);
}

float launch_ray(t_cub3d c3d, float angle);
int main(int argc, char *argv[])
{
	t_cub3d	c3d;

	if (argc != 2)
		return (1);
	c3d = initializer(open(argv[1], O_RDONLY));
	mlx_hook(c3d.mlxgraph.win, 2, 1L<<0, move, &c3d.player);
	mlx_hook(c3d.mlxgraph.win, 3, 1L<<1, unmove, &c3d.player);
	mlx_loop_hook(c3d.mlxgraph.mlx, main_loop, &c3d);
	mlx_do_key_autorepeatoff(c3d.mlxgraph.mlx);
	mlx_loop(c3d.mlxgraph.mlx);
}