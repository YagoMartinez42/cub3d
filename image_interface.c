/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:25:06 by bvelasco          #+#    #+#             */
/*   Updated: 2025/02/23 18:22:42 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	img_into_img(t_texture target, t_texture mini, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < mini.ht)
	{
		j = 0;
		while (j < mini.wd)
		{
			*(int *)(target.addr + (x + j
						+ (target.wd * y) + (target.wd * i)))
				= *(int *)(mini.addr + (j + (mini.wd * i)));
			j++;
		}
		i++;
	}
}

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
