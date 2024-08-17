/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:22:38 by samartin          #+#    #+#             */
/*   Updated: 2024/08/17 18:59:34 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		rcode;
	map_t	*map;

	rcode = cb_startup(argc, argv, map);
	if (rcode)
		return (rcode);
	//Play loop
	//Clean-up
	return (0);
}