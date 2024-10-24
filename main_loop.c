/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:39 by bvelasco          #+#    #+#             */
/*   Updated: 2024/10/21 17:54:14by bvelasco         ###   ########.fr       */
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

void	drawline(void *c3d, int j, float k)
{
	const t_cub3d	*cub3d = c3d;
	float	h = (WINH*32)/k;
	int		i;
	int		l;

	i = 0;
	while (i < WINH/2)
	{
		screenbuff_pixel_put(cub3d->mlxgraph.scrnbuff, j, i, 0xFF00);
		i++;
	}
	while (i < WINH)
	{
		screenbuff_pixel_put(cub3d->mlxgraph.scrnbuff, j, i, 0x0);
		i++;
	}
	l = -h/2;
	while (l < +h/2)
	{
		screenbuff_pixel_put(cub3d->mlxgraph.scrnbuff, j, roundf(WINH/2 + l), 0x00FFFFFF);
		l++;
	}
}


int	main_loop(void *c3d)
{
	t_cub3d		*cub3d;
	float		i;
	int			j = 0;
	float		pixel_angle;

	cub3d = c3d;
	cub3d = c3d;
	move_player(&cub3d->player);
	i = -(FOV) / 2;
	pixel_angle = FOV/WINW;	
	while (j < WINW)
	{
		float k = launch_ray(*cub3d, cub3d->player.aov - (i * (M_PI / 180)));

		k = k + (cos((i * (M_PI/180)) - cub3d->player.aov));
		i += pixel_angle;
		drawline(c3d,j,k);
		j++;
	}
	mlx_put_image_to_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win, cub3d->mlxgraph.scrnbuff->img, 0, 0);
	return (0);
}
