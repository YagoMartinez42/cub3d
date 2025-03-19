/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:39 by bvelasco          #+#    #+#             */
/*   Updated: 2025/03/19 20:45:41 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	dda_movement(float *original_cords, float *final_cords, t_map *map)
{
	float		steps;
	float		step_x;
	float		step_y;
	const float	dist[2] = {final_cords[X] - original_cords[X],
		final_cords[Y] - original_cords[Y]};
	const float	min_move = 0.008;

	if (fabsf(dist[X]) >= fabsf(dist[Y]))
		steps = fabsf(dist[X]);
	else
		steps = fabsf(dist[Y]);
	step_x = dist[X] / steps;
	step_y = dist[Y] / steps;
	(void) map;
	while (steps > min_move)
	{
		if (detect_colision(original_cords[Y] + (step_y * min_move),
				original_cords[X] + (step_x * min_move), map))
			return ;
		original_cords[X] += (step_x * min_move);
		original_cords[Y] += (step_y * min_move);
		steps -= min_move;
	}
}

static void	move_player(t_player *player, float sbf)
{
	float	final_cords[2];

	final_cords[X] = player->coords[X] + player->xmov
		* (VEL * sbf) * cosf(player->aov + M_PI_2);
	final_cords[Y] = player->coords[Y] + player->xmov
		* (VEL * sbf) * sinf(player->aov + M_PI_2);
	final_cords[X] += player->ymov * (VEL * sbf)
		* cosf(player->aov + M_PI);
	final_cords[Y] += player->ymov * (VEL * sbf)
		* sinf(player->aov + M_PI);
	dda_movement(player->coords, final_cords, &player->map);
	player->aov += (player->rotate * (M_PI / 180)) * (VEL * sbf) * 20;
	return ;
}

static float	seconds_before_this_frame(void)
{
	static long		last_sec = 0;
	static long		last_usec = 0;
	static int		is_started = 0;
	struct timeval	time;
	float			result;

	gettimeofday(&time, NULL);
	if (is_started)
	{
		result = (time.tv_sec - last_sec)
			+ ((time.tv_usec - last_usec) / pow(10, 6));
		if (result < 1 / 60)
			return (-1);
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
	float		dda_data[2];
	int			j;
	float		sbf;
	t_hitpoint	col;

	cub3d = c3d;
	sbf = seconds_before_this_frame();
	if (sbf == -1)
		return (1);
	move_player(&cub3d->player, sbf);
	j = 0;
	dda_data[0] = ((FOV) / 2);
	print_minimap(&cub3d->player.map, cub3d->mlxgraph.minimap);
	while (j < WINW)
	{
		dda_data[1] = launch_ray(&cub3d->player, cub3d->player.aov
				- (dda_data[0] * (M_PI / 180)), cub3d->mlxgraph.minimap, &col);
		dda_data[0] -= FOV / WINW;
		print_column(c3d, roundf(WINH / dda_data[1]), j, col);
		j++;
	}
	if (cub3d->player.minimap)
		img_into_img(*cub3d->mlxgraph.scrnbuff, *cub3d->mlxgraph.minimap->texture, 0, 0);
	mlx_put_image_to_window(cub3d->mlxgraph.mlx, cub3d->mlxgraph.win,
		cub3d->mlxgraph.scrnbuff->img, 0, 0);
	return (0);
}
