/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:07:19 by samartin          #+#    #+#             */
/*   Updated: 2024/08/17 19:03:59 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	cb_errors(int code)
{
	if (code == 101)
		perror("Error\n Usage is \"cub3d [path to map file .cub]\"\n");
	if (code == 102)
		perror("Error\n Could not load map file\n");
	else
		perror("Error\n Untracked error\n");
	return (code);
}