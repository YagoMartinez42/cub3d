/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:24:32 by samartin          #+#    #+#             */
/*   Updated: 2024/09/05 15:47:27 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include "libft/include/libft.h"
# include "player.h"
# include "raycasting.h"

//Startup
__int8_t	cb_startup(int argc, char **argv, t_map *map);

//Init and Load
t_mlxgrph	*cb_init_n_load(t_map *map);

//Error Management
__int8_t	cb_errors(__int8_t code);
void	cb_fatal_errors(__int8_t code);

#endif
