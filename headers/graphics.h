/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:55:00 by bvelasco          #+#    #+#             */
/*   Updated: 2024/12/09 14:03:16 by bvelasco         ###   ########.fr       */
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
typedef void	t_mlxwin;
typedef void	t_mlximg;

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
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			wd;
	int			ht;
}				t_texture;

//mlx grph struct
typedef struct s_mlxgrph
{
	t_mlx		*mlx;
	t_mlxwin	*win;
	t_texture	*scrnbuff;
}		t_mlxgrph;

/**
 * Type texture column: Used to mark a single column of pixels inside a texture.
 * @var texture: t_texture from which to select the column.
 * @var column: Horizontal index of the column.
 */
typedef struct s_texture_column
{
	int			ray;
	t_texture	*texture;
	int32_t		floor_color;
	int32_t		ceil_color;
	float		wall_point;
}				t_texture_column;

t_mlxgrph	*mlxgrph_new(void *mlx);
void		destroy_window(t_mlxgrph *this);
void		ft_image_pixel_put(t_texture *texture, int x, int y, int color);
void		print_column(t_texture buffer, t_texture_column tcol, int size);
#endif
