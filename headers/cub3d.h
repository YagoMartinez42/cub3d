/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:24:32 by samartin          #+#    #+#             */
/*   Updated: 2024/12/02 12:29:52 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <inttypes.h>
# include "../libft/include/libft.h"
# include "error_management.h"
# include "graphics.h"
# include "map.h"
# include "player.h"
# ifndef WINW
#  define WINW 800
# endif
# ifndef WINH
#  define WINH 600
# endif
# ifndef BPP
#  define BPP 4
# endif

typedef struct s_cub3d
{
	t_mlxgrph	mlxgraph;
	t_player	player;
	uint8_t		is_valid;
}				t_cub3d;

#endif
