/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:10:40 by samartin          #+#    #+#             */
/*   Updated: 2024/11/19 11:40:23 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_MAP_H
# define NEW_MAP_H

__uint8_t	c3d_read_header(int fd, t_map *map, t_mlx *mlx);
__uint8_t	c3d_read_map(int fd, t_map *map);
__uint8_t	c3d_validate_map(char **map_matrix);

//Matrix utils
__uint8_t	c3d_matrix_health_3(char **matrix);
__uint8_t	c3d_clear_header(char **header);
__uint8_t	c3d_free2d(char **array_of_str);
void		c3d_cpynfill(char *dest, char *src, size_t full_l);

//Error management
__int8_t	c3d_errors(__int8_t code);
void		c3d_fatal_errors(__int8_t code);

#endif