/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrnbuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:25:06 by bvelasco          #+#    #+#             */
/*   Updated: 2024/11/19 10:25:12 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	scrnbuff_pixel_put(t_texture	*texture, int x, int y, int color)
{
	if (x < 0 || x > WINW || y < 0 || y > WINH)
		return ;
	texture->addr[(WINW * y) + x] = color;
}
