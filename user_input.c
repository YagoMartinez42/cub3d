/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:35:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/29 12:59:23 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	move(int keycode, void *param)
{
	t_player	*player;

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
	if (keycode == 32)
	{
		if (player->minimap)
			player->minimap = 0;
		else
			player->minimap = 1;
	}
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
		player->xmov += 1;
	if (keycode == 97)
		player->xmov -= 1;
	if (keycode == 115)
		player->ymov -= 1;
	if (keycode == 119 && player->ymov < 0)
		player->ymov += 1;
	return (0);
}
