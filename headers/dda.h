/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:38:43 by bvelasco          #+#    #+#             */
/*   Updated: 2025/04/01 17:39:50 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H
# include "cub3d.h"

typedef struct s_dda
{
	float		trig[3];
	float		dirs[2];
	float		remains[2];
	int			crds_int[2];
	t_hitpoint	*ht_data;
}				t_dda;

void	get_remains(float *dir, float *remains, float *crds, int *crds_int);
#endif
