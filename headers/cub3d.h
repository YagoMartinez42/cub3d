/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:24:32 by samartin          #+#    #+#             */
/*   Updated: 2025/02/12 13:36:30 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
#include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <inttypes.h>
# include "../libft/include/libft.h"
# include "error_management.h"
# include "graphics.h"
# include "map.h"
# include "player.h"
# ifndef WINW
#  define WINW 1440
# endif
# ifndef WINH 
#  define WINH 1080
# endif
# ifndef BPP
#  define BPP 4
# endif
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

enum	e_direction
{
	X,
	Y
};
typedef struct s_cub3d
{
	t_mlxgrph	mlxgraph;
	t_player	player;
	uint8_t		is_valid;
}				t_cub3d;

#endif
