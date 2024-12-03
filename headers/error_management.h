/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:28:10 by samartin          #+#    #+#             */
/*   Updated: 2024/12/02 12:32:48 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H

int8_t	c3d_errors(int8_t code);
void	c3d_fatal_errors(int8_t code);
void	c3d_close_n_exit(void *mlx, int8_t code);

#endif