/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:07:19 by samartin          #+#    #+#             */
/*   Updated: 2024/09/05 15:48:01 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__int8_t	cb_errors(__int8_t code)
{
	if (code == 1)
		perror("Error\n Usage is \"cub3d [path to map file .cub]\"\n");
	if (code == 2)
		perror("Error\n Could not load map file\n");
	if (code == 3)
		perror("Error\n Could not load texture\n");
	else
		perror("Error\n Untracked error\n");
	return (code);
}

void	cb_fatal_errors(__int8_t code)
{
	if (code == -1)
		perror("Error: Unable to allocate memory\n");
	if (code == -2)
		perror("Error: Unable to open file\n");
	if (code == -3)
		perror("Error: Could not initialize MinilibX\n");
	else
		perror("Error\n Untracked fatal error\n");
	exit(code);
}
