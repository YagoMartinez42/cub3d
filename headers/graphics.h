/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:55:00 by bvelasco          #+#    #+#             */
/*   Updated: 2024/11/18 16:09:54 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "cub3d.h"

/**
 * Type MinilibX Graphic Controller: Contains the two pointers needed by most
 *  MLX functions.
 * @var mlx: Void pointer to the mlx display server instance, created by the
 *  `mlx_init` function.
 * @var win: Void pointer to the window instance, created by the
 *  `mlx_new_window` function.
 */
//mlx typedefs
typedef void	t_mlx;
typedef void	t_mlximg;
typedef void	t_mlxwin;
typedef void	t_scrbuff;

typedef struct s_mlxgrph
{
	t_mlx		*mlx;
	t_mlxwin	*win;
	t_scrbuff	*scrnbuff;
}		t_mlxgrph;

/**
 * Type MinilibX Texture: An image struct to be used by MLX functions. We add
 *  width and height info for easiness in custom functions.
 * @var img: The starting address of the image as a whole. Returned by
 *  `mlx_new_image` function.
 * @var addr: The starting address of the pixel data of that image. Returned by
 *  `mlx_get_data_addr` function.
 * @var line_length: Byte length of a line of the image. Set by reference by
 *  `mlx_get_data_addr` function.
 * @var endian: Boolean value to mark little or bit endian in the data. Set by
 *  reference by `mlx_get_data_addr` function.
 * @var wd: Pixel width of the image. Set and used by Cub3D functions.
 * @var ht: Pixel height of the image. Set and used by Cub3D functions.
 */
typedef struct s_texture
{
	t_mlximg	*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			wd;
	int			ht;
}				t_texture;


/**
 * Type texture column: Used to make an equivalency between column of pixels in
 *  the texture and column of pixels in the window buffer.
 * @var ray: number of ray starting from zero. There is one ray for each window
 *  horizontal pixel.
 * @var texture: t_texture from which to select the column.
 * @var floor_color: RGBA quad in a single int, for floor visual region.
 * @var ceil_color: RGBA quad in a single int, for ceiling visual region.
 * @var wal_point: Horizontal position of the column in a range 0-1.
 */
typedef struct	s_texture_column
{
	int			ray;
	t_texture	*texture;
	int32_t		floor_color;
	int32_t		ceil_color;
	float		wall_point;
}				t_texture_column;

t_mlxgrph	*mlxgrph_new(void *mlx);
void		destroy_window(t_mlxgrph *this);
void		print_column(t_texture buffer, t_texture_column tcol, int size);
#endif
