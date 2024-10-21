/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:39 by bvelasco          #+#    #+#             */
/*   Updated: 2024/10/21 15:24:38 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	move_player(t_player *player)
{
	if (!detect_colision((player->coords[1]
				+ player->xmov * VEL * cosf(player->aov + M_PI_2)) / 32
			, (player->coords[0] + player->xmov * VEL
				* sinf(player->aov + M_PI_2)) / 32, player->map))
	{
		player->coords[0] += player->xmov * VEL * sinf(player->aov + M_PI_2);
		player->coords[1] += player->xmov * VEL * cosf(player->aov + M_PI_2);
	}
	if (!detect_colision((player->coords[1]
				+ player->ymov * VEL * cosf(player->aov + M_PI)) / 32
			, (player->coords[0] + player->ymov * VEL
				* sinf(player->aov + M_PI)) / 32, player->map))
	{
		player->coords[0] += player->ymov * VEL * sinf(player->aov + M_PI);
		player->coords[1] += player->ymov * VEL * cosf(player->aov + M_PI);
	}
	player->aov += (player->rotate * (M_PI / 180)) * VEL;
	return ;
}

int	main_loop(void *c3d)
{
	t_cub3d		*cub3d;
	t_player	*play;
	float		i;
	int			j = 0;
	float		pixel_angle;

	cub3d = c3d;
	play = &cub3d->player;
	usleep(20000);
	mlx_clear_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win);
	move_player(play);
	i = -FOV / 2;
	pixel_angle = FOV/WINW;	
	while (j < WINW)
	{
		float k = launch_ray(*cub3d, play->aov - (i * (M_PI / 180)));
		mlx_pixel_put(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win, j, k, 0xffffff);
		mlx_pixel_put(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win, j, WINH -k, 0xffffff);
		j++;
		i += pixel_angle;
	}
	return (0);
}
