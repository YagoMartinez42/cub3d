/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:22:38 by samartin          #+#    #+#             */
/*   Updated: 2024/08/21 13:44:04 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	uint8_t	rcode;
	t_map	*map;

	rcode = cb_startup(argc, argv, map);
	if (rcode)
		return (rcode);
	//Play loop
	//Clean-up
	return (0);
}
