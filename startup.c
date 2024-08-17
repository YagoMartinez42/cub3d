/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:03:15 by samartin          #+#    #+#             */
/*   Updated: 2024/08/17 19:05:09 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Check .cub extension
//Load Map
	// ...
//Parse map to struct
	// ...
//Validate map content
	// ...
//Load textures

int	cb_startup(int argc, char **argv, map_t *map)
{
	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (cb_errors(101));
	map = cb_load_map(argv[1]); // <--TO DO
	if (!map)
		return (cb_errors(103));
	return(0);
}
