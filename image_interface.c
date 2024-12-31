/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrnbuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:25:06 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/09 14:02:19 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	ft_image_pixel_put(t_texture	*texture, int x, int y, int color)
{
	if (!texture || x < 0 || x > texture->wd || y < 0 || y > texture->ht)
		return ;
	texture->addr[(texture->wd * y) + x] = color;
}

t_texture	*new_texture(void *c3d, int width, int height)
{
	t_texture			*texture;
	const t_cub3d		*cub3d = c3d;

	texture = malloc(sizeof(t_texture));
	texture->img = mlx_new_image(cub3d->mlxgraph.mlx, width, height);
	texture->addr = (void *) mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	texture->wd = width;
	texture->ht = height;
	return (texture);
}