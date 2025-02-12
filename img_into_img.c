/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_into_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:10 by samartin          #+#    #+#             */
/*   Updated: 2025/02/12 12:46:23 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/graphics.h"

void	img_into_img(t_texture target, t_texture mini, int *pos)
{
	int	i;
	int	j;

	i = 0;
	while (i < mini.ht)
	{
		j = 0;
		while (j < mini.wd)
		{
			*(int *)(target.addr + (pos[X] + j
				+ (target.wd * pos[Y]) + (target.wd * i)))
				= *(int *)(mini.addr + (j + (mini.wd * i)));
			j++;
		}
		i++;
	}
}
