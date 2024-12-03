/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:28:43 by samartin          #+#    #+#             */
/*   Updated: 2024/12/03 12:57:04 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/graphics.h"

static float	set_wall_pixel(t_texture buffer, t_texture_column tcol,
	int offset,	float vpoint)
{
	int		tex_offset;
	float	v_increase;

	tex_offset = ((int)(tcol.wall_point * tcol.texture->wd) * BPP)
		+ (tcol.texture->wd * (int)(vpoint * tcol.texture->ht) * BPP);
	*(int *)(buffer.addr + offset) = *(int *)(tcol.texture->addr
			+ tex_offset);
	return (v_increase);
}

void	print_column(t_texture buffer, t_texture_column tcol, int size)
{
	int		y;
	int		offset;
	float	vpoint;

	if (size > buffer.ht)
		vpoint = 1 - (buffer.ht / size);
	else
		vpoint = 0;
	y = 0;
	while (y < buffer.ht)
	{
		offset = (tcol.ray * BPP) + (buffer.wd * y * BPP);
		if (y < ((buffer.ht - size) / 2))
			*(int *)(buffer.addr + offset) = tcol.ceil_color;
		else if (y > (size + ((buffer.ht - size) / 2)))
			*(int *)(buffer.addr + offset) = tcol.floor_color;
		else
		{
			set_wall_pixel(buffer, tcol, offset, vpoint);
			vpoint += (1 / tcol.texture->ht) * (buffer.ht / size);
		}
		y++;
	}
}
