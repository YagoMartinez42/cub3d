/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:28:43 by samartin          #+#    #+#             */
/*   Updated: 2025/03/08 12:13:51 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	set_wall_pixel(t_texture *imgs, int offset, t_hitpoint cpoint,
	float vpoint)
{
	int	tex_offset;

	if (cpoint.wall_pos == SOUTH || cpoint.wall_pos == WEST)
		cpoint.w_point = 1 - cpoint.w_point;
	tex_offset = (int)(cpoint.w_point * imgs[1].wd) + ((imgs[1].wd
				* (int)(vpoint * (imgs[1].ht))));
	*(int *)(imgs[0].addr + offset) = *(int *)(imgs[1].addr + tex_offset);
}

void	print_column(t_cub3d *c3d, int size, int ray, t_hitpoint cpoint)
{
	int			y;
	int			offset;
	float		vpoint;
	const float	v_increase = 1.0F / size;
	t_texture	imgs [2];

	imgs[0] = *(c3d->mlxgraph.scrnbuff);
	imgs[1] = c3d->player.map.walls[cpoint.wall_pos];
	vpoint = 0.0F;
	if (size > imgs[0].ht)
		vpoint = (1.0F - ((float)imgs[0].ht / size)) / 2;
	y = -1;
	while (++y < imgs[0].ht)
	{
		offset = (ray + (imgs[0].wd * y));
		if (y <= ((imgs[0].ht - size) / 2))
			*(int *)(imgs[0].addr + offset) = c3d->player.map.ceil_color;
		else if (y >= (size + ((imgs[0].ht - size) / 2)))
			*(int *)(imgs[0].addr + offset) = c3d->player.map.floor_color;
		else
		{
			set_wall_pixel(imgs, offset, cpoint, vpoint);
			vpoint += v_increase;
		}
	}
}
