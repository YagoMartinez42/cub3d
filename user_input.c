/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:35:07 by bvelasco          #+#    #+#             */
/*   Updated: 2025/03/09 16:31:01 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	mouse_abling(void *c3d)
{
	t_mlxgrph	*mlx;
	t_player	*player;

	mlx = &(((t_cub3d *)c3d)->mlxgraph);
	player = &(((t_cub3d *)c3d)->player);
	if (player->mouse_lock)
	{
		player->mouse_lock = 0;
		mlx_mouse_show(mlx->mlx, mlx->win);
		player->rotate = 0;
	}
	else
	{
		player->rotate = 0;
		player->mouse_lock = 1;
		mlx_mouse_move(mlx->mlx, mlx->win, WINW / 2, WINH / 2);
		mlx_mouse_hide(mlx->mlx, mlx->win);
	}
	player->rotate = 0;
}

int	move(int keycode, void *param)
{
	t_player	*player;

	player = &((t_cub3d *)param)->player;
	if (keycode == 65361 && player->mouse_lock == 0)
		player->rotate = -1;
	if (keycode == 65363 && player->mouse_lock == 0)
		player->rotate = +1;
	if (keycode == 100)
		player->xmov = 1;
	if (keycode == 97)
		player->xmov = -1;
	if (keycode == 115)
		player->ymov = 1;
	if (keycode == 119)
		player->ymov = -1;
	if (keycode == 109)
	{
		if (player->minimap)
			player->minimap = 0;
		else
			player->minimap = 1;
	}
	if (keycode == 44)
		mouse_abling(param);
	return (0);
}

int	unmove(int keycode, void *param)
{
	t_player	*player;

	player = param;
	if (keycode == 65361)
		player->rotate = 0;
	if (keycode == 65363)
		player->rotate = 0;
	if (keycode == 100)
		player->xmov = 0;
	if (keycode == 97)
		player->xmov = 0;
	if (keycode == 115)
		player->ymov = 0;
	if (keycode == 119 && player->ymov < 0)
		player->ymov = 0;
	return (0);
}

void	mouse_rotation(void *cub3d)
{
	int			x;
	int			y;
	static int	frcount;
	t_cub3d		*c3d;

	c3d = (t_cub3d *)cub3d;
	if (c3d->player.mouse_lock)
	{
		mlx_mouse_get_pos(c3d->mlxgraph.mlx, c3d->mlxgraph.win, &x, &y);
		if (x < ((WINW / 2) - 1))
			c3d->player.rotate = -1;
		else if (x > ((WINW / 2) + 1))
			c3d->player.rotate = 1;
		else
			c3d->player.rotate = 0;
		frcount++;
		if (frcount > 4)
		{
			frcount = 0;
			mlx_mouse_move(c3d->mlxgraph.mlx, c3d->mlxgraph.win, WINW / 2,
				WINH / 2);
		}
	}
}
