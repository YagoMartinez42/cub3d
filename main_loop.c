/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:39 by bvelasco          #+#    #+#             */
/*   Updated: 2025/01/09 14:58:05 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	move_player(t_player *player)
{
	if (!detect_colision((player->coords[1]
				+ player->xmov * VEL * sinf(player->aov + M_PI_2))
			, (player->coords[0] + player->xmov * VEL
				* cosf(player->aov + M_PI_2)), &player->map))
	{
		player->coords[0] += player->xmov * VEL * cosf(player->aov + M_PI_2);
		player->coords[1] += player->xmov * VEL * sinf(player->aov + M_PI_2);
	}
	if (!detect_colision((player->coords[1]
				+ player->ymov * VEL * sinf(player->aov + M_PI))
			, (player->coords[0] + player->ymov * VEL
				* cosf(player->aov + M_PI)), &player->map))
	{
		player->coords[0] += player->ymov * VEL * cosf(player->aov + M_PI);
		player->coords[1] += player->ymov * VEL * sinf(player->aov + M_PI);
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
	h = roundf(WINH / k);
	while (i < WINH / 2)
	{
		ft_image_pixel_put(cub3d->mlxgraph.scrnbuff, j, i, 0x87CEEB);
		i++;
	}
	while (i < WINH)
	{
		ft_image_pixel_put(cub3d->mlxgraph.scrnbuff, j, i, 0xA0522D);
		i++;
	}
	l = -h / 2;
	h_2 = h / 2;
	while (l < h_2)
	{
		ft_image_pixel_put(cub3d->mlxgraph.scrnbuff, j, WINH / 2 + l, 0x8B8B8B);
		l++;
	}
}

int	game_loop(void *c3d)
{
	t_cub3d		*cub3d;
	float		i;
	int			j;
	float		k;

	cub3d = c3d;
	move_player(&cub3d->player);
	j = 0;
	i = (FOV) / 2;
	print_minimap(&cub3d->player.map, cub3d->mlxgraph.minimap);
	while (j < WINW)
	{
		k = launch_ray(&cub3d->player, cub3d->player.aov - (i * (M_PI / 180)),
				cub3d->mlxgraph.minimap, NULL);
		i -= FOV / WINW;
		drawline(c3d, j, k);
		j++;
	}
	mlx_put_image_to_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win,
		cub3d->mlxgraph.scrnbuff->img, 0, 0);
	if (cub3d->player.minimap)
		mlx_put_image_to_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win,
			cub3d->mlxgraph.minimap->texture->img, 0, 0);
	return (0);
}
