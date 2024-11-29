/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:28:43 by samartin          #+#    #+#             */
/*   Updated: 2024/11/28 17:16:57 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/graphics.h"

void	print_column(t_texture buffer, t_texture_column tcol, int size)
{
	int		y;
	int		offset;
	int		tex_offset;
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
			tex_offset = ((int)(tcol.wall_point * tcol.texture->wd) * BPP) + (tcol.texture->wd * (int)(vpoint * tcol.texture->ht) * BPP);
			*(int *)(buffer.addr + offset) = *(int *)(tcol.texture->addr + tex_offset);
			vpoint += (1 / tcol.texture->ht) * (buffer.ht / size);
		}
printf("y = %d; offset = %d; tex_offset = %d; vpoint = %f\n", y, offset, tex_offset, vpoint);
		y++;
	}
}
