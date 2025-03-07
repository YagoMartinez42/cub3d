/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:39 by bvelasco          #+#    #+#             */
/*   Updated: 2025/01/21 09:52:55y bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	move_player(t_player *player, float sbf)
{
	if (!detect_colision((player->coords[1]
				+ player->xmov * (VEL * sbf) * sinf(player->aov + M_PI_2))
			, (player->coords[0] + player->xmov * (VEL * sbf)
				* cosf(player->aov + M_PI_2)), &player->map))
	{
		player->coords[0] += player->xmov * (VEL * sbf) * cosf(player->aov + M_PI_2);
		player->coords[1] += player->xmov * (VEL * sbf) * sinf(player->aov + M_PI_2);
	}
	if (!detect_colision((player->coords[1]
				+ player->ymov * (VEL * sbf) * sinf(player->aov + M_PI))
			, (player->coords[0] + player->ymov * (VEL * sbf)
				* cosf(player->aov + M_PI)), &player->map))
	{
		player->coords[0] += player->ymov * (VEL * sbf) * cosf(player->aov + M_PI);
		player->coords[1] += player->ymov * (VEL * sbf) * sinf(player->aov + M_PI);
	}
	player->aov += (player->rotate * (M_PI / 180)) * (VEL * sbf) * 20 ;
	return ;
}

static float	seconds_before_this_frame()
{
	static long		last_sec = 0;
	static long		last_usec = 0;
	static int		is_started = 0;
	struct timeval	time;
	float			result;

	gettimeofday(&time, NULL);
	if (is_started)
	{
		result = (time.tv_sec - last_sec) +
			((time.tv_usec - last_usec)/pow(10,6));
	}
	else
	{
		result = 0;
		is_started = 1;
	}
	last_sec = time.tv_sec;
	last_usec = time.tv_usec;
	return (result);
}

int	game_loop(void *c3d)
{
	t_cub3d		*cub3d;
	float		i;
	int			j;
	float		k;
	t_hitpoint	col;

	cub3d = c3d;
	move_player(&cub3d->player, seconds_before_this_frame());
	j = 0;
	i = ((FOV) / 2);
	print_minimap(&cub3d->player.map, cub3d->mlxgraph.minimap);
	while (j < WINW)
	{
		k = launch_ray(&cub3d->player, cub3d->player.aov - (i * (M_PI / 180)),
				cub3d->mlxgraph.minimap, &col);
		if (i <= 0.001 && i >= -0.001)
			printf("Central ray: %f\n", k);
		i -= FOV / WINW;
		print_column(c3d, roundf(WINH / k), j, col);
		j++;
	}
	if (cub3d->player.minimap)
		img_into_img(*cub3d->mlxgraph.scrnbuff, *cub3d->mlxgraph.minimap->texture, 0, 0);
	mlx_put_image_to_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win,
		cub3d->mlxgraph.scrnbuff->img, 0, 0);
	return (0);
}
