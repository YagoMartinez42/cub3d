/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:39 by bvelasco          #+#    #+#             */
/*   Updated: 2024/11/19 16:59:36 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	move_player(t_player *player)
{
	if (!detect_colision((player->coords[1]
				+ player->xmov * VEL * cosf(player->aov + M_PI_2))
			, (player->coords[0] + player->xmov * VEL
				* sinf(player->aov + M_PI_2)), *player->map, NULL))
	{
		player->coords[0] += player->xmov * VEL * sinf(player->aov + M_PI_2);
		player->coords[1] += player->xmov * VEL * cosf(player->aov + M_PI_2);
	}
	if (!detect_colision((player->coords[1]
				+ player->ymov * VEL * cosf(player->aov + M_PI))
			, (player->coords[0] + player->ymov * VEL
				* sinf(player->aov + M_PI)), *player->map, NULL))
	{
		player->coords[0] += player->ymov * VEL * sinf(player->aov + M_PI);
		player->coords[1] += player->ymov * VEL * cosf(player->aov + M_PI);
	}
	player->aov += (player->rotate * (M_PI / 180)) * VEL * 20;
	return ;
}

void	drawline(void *c3d, int j, float k)
{
	const t_cub3d	*cub3d = c3d;
	float			h;
	int				i;
	int				l;
	int				h_2;

	i = 0;
	h = (WINH / k);
	while (i < WINH / 2)
	{
		scrnbuff_pixel_put(cub3d->mlxgraph.scrnbuff, j, i, 0xFF00);
		i++;
	}
	while (i < WINH)
	{
		scrnbuff_pixel_put(cub3d->mlxgraph.scrnbuff, j, i, 0x0);
		i++;
	}
	l = -h / 2;
	h_2 = h / 2;
	while (l < h_2)
	{
		scrnbuff_pixel_put(cub3d->mlxgraph.scrnbuff, j, WINH / 2 + l, 0xFFFFFF);
		l++;
	}
}

int	main_loop(void *c3d)
{
	t_cub3d		*cub3d;
	float		i;
	int			j;
	float		k;
	float		pixel_angle;
	float		**col_point;

	col_point = malloc(2 * sizeof(void *));
	col_point[0] = malloc(sizeof(float));
	col_point[1] = malloc(sizeof(float));
	cub3d = c3d;
	cub3d = c3d;
	move_player(&cub3d->player);
	j = 0;
	i = -(FOV) / 2;
	pixel_angle = FOV / WINW;
	while (j < WINW)
	{
		k = launch_ray(*cub3d, cub3d->player.aov - (i * (M_PI / 180)),
			col_point);
		i += pixel_angle;
		drawline(c3d, j, k);
		j++;
	}
	mlx_put_image_to_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win,
		cub3d->mlxgraph.scrnbuff->img, 0, 0);
	return (0);
}
