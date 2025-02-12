/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:55:00 by bvelasco          #+#    #+#             */
/*   Updated: 2025/01/02 16:38:56by bvelasco         ###   ########.fr       */
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

/*
 * @var texture: Texture of the map
 * @var size: size (in pixels) for every map cell
*/

typedef struct s_minimap
{
	t_texture	*texture;
	int			size;
}				t_minimap;

//mlx grph struct
typedef struct s_mlxgrph
{
	t_mlx			*mlx;
	t_mlxwin		*win;
	t_texture		*scrnbuff;
	t_minimap		*minimap;
}		t_mlxgrph;


typedef struct s_hitpoint
{
	int		hit_dir;	
	float	w_point;
	int		wall_pos;
}				t_hitpoint;


t_mlxgrph	*mlxgrph_new(void *mlx);
t_texture	*new_texture(void *c3d, int width, int height);
t_minimap	*new_minimap(void *c3d);
void		destroy_window(t_mlxgrph *this);
void		ft_image_pixel_put(t_texture *texture, int x, int y, int color);
void		print_column(void *c3d, int size, t_colpoint cpoint);
void		img_into_img(t_texture target, t_texture mini, int *pos);
#endif
