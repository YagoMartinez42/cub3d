/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_remains.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:40:04 by bvelasco          #+#    #+#             */
/*   Updated: 2025/04/01 17:40:57 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/dda.h"

void	get_remains(float *dir, float *remains, float *crds, int *crds_int)
{
	if (dir[X] > 0)
		remains[X] = crds[X] - crds_int[X];
	else
		remains[X] = 1 - (crds[X] - crds_int[X]);
	if (dir[Y] > 0)
		remains[Y] = crds[Y] - crds_int[Y];
	else
		remains[Y] = 1 - (crds[Y] - crds_int[Y]);
}
