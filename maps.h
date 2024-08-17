/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:46:18 by samartin          #+#    #+#             */
/*   Updated: 2024/08/17 18:58:29 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H
# include "libft/include/libft.h"
# ifndef WINW
#  define WINW 1280
# endif
# ifndef WINH
#  define WINH 720
# endif
# ifndef TEXW
#  define TEXW 128
# endif
# ifndef TEXH
#  define TEXH 128
# endif
# ifndef BPP
#  define BPP sizeof(int32_t)
# endif

typedef	struct map_s
{
	size_t	map_size[2];
	int32_t	floor_color;
	int32_t	ceil_color;
	t_list	*txtr_lst;
	char	**map_matrix;
}	map_t;

#endif
