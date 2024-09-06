/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:51:58 by samartin          #+#    #+#             */
/*   Updated: 2024/09/05 18:39:22 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlxgrph *cb_init_n_load(t_map *map)
{
	t_mlxgrph	*mlx;
	t_list		*node;
	char		*tpath;
	t_texture	*img;

	mlx = malloc(sizeof(t_mlxgrph));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINW, WINH, "Cub3D");
	node = map->txtr_lst;
	while (node)
	{
		tpath = map->txtr_lst->content.str;
		img = ft_calloc(1, sizeof(t_texture));
		img->img = mlx_xpm_file_to_image(mlx->mlx, tpath, &img->wd, &img->ht);
		node->content.ptr = img;
		node = node->next;
		free(tpath);
	}
	return (mlx);
}
