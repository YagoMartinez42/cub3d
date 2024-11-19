/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:26 by samartin          #+#    #+#             */
/*   Updated: 2024/11/19 16:58:29 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# ifndef FOV
#  define FOV 60.0f
# endif
# ifndef VEL
#  define VEL 0.1f
# endif

/**
 * Type Player: Contains all the needed values to execute movement in a grid and
 *  raycasting representation. It is used along with the constant `FOV` (field
 *  of view).
 * @var map: t_map struct containing horizontal and vertical size, two colors
 *  for ceiling and floor and a 2D matrix with the scenario distribution.
 * @var coords: An array of 2 floats representing the X and Y position of the
 *  player on the map.
 * @var aov: Angle of View, a single float containing an angle in degrees
 *  representing the camera orientation relative to the zero point (North).
 *  
*/
typedef struct s_player
{
	t_map	*map;
	float	coords[2];
	float	aov;
	int		xmov;
	int		ymov;
	int		rotate;
}				t_player;

t_player	player_new(t_map *map);
void		play_destroy(t_player *this);
void		player_move(t_player *this, int dirx, int diry);
int			move(int keycode, void *param);
int			unmove(int keycode, void *param);
int			main_loop(void *c3d);
int			detect_colision(float y, float x, t_map map, float *col_point[]);
t_player	init_player(t_map map);

#endif
