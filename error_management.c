/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:07:19 by samartin          #+#    #+#             */
/*   Updated: 2024/11/20 15:28:58 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

__int8_t	c3d_errors(__int8_t code)
{
	if (code == 1)
		write (2, "Error\nUsage is \"cub3d [path to map file .cub]\"\n", 47);
	if (code == 2)
		write (2, "Error\nCould not load map file\n", 30);
	if (code == 3)
		write (2, "Error\nCould not load texture\n", 29);
	if (code == 4)
		write (2, "Error\nCould not process map\n", 28);
	else
		perror("Error\n Untracked error\n");
	return (code);
}

void	c3d_fatal_errors(__int8_t code)
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

void	c3d_close_n_exit(t_mlx *mlx, int8_t code)
{
	mlx_destroy_display(mlx);
	c3d_errors(code);
	exit(code);
}
