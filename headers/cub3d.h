/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:24:32 by samartin          #+#    #+#             */
/*   Updated: 2024/10/18 13:14:48 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "../libft/include/libft.h"
# include "graphics.h"
# include "map.h"
# include "player.h"
# ifndef WINW
#  define WINW 1920
# endif
# ifndef WINH
#  define WINH 1080
# endif
# ifndef BPP
#  define BPP 4
# endif

typedef struct s_cub3d
{
	t_mlxgrph	mlxgraph;
	t_map		map;
	t_player	player;
}				t_cub3d;

float	launch_ray(t_cub3d c3d, float angle);
#endif
