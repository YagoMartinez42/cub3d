/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:24:32 by samartin          #+#    #+#             */
/*   Updated: 2024/08/17 19:04:15 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include "libft/include/libft.h"
# include "MLX42/MLX42.h"
# include "maps.h"

//Startup
int	cb_startup(int argc, char **argv, map_t *map);

//Error Management
int	cb_errors(int code);

#endif
