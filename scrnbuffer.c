#include "headers/cub3d.h"

void	screenbuff_pixel_put(t_texture	*texture, int x, int y, int color)
{
	if (x < 0 || x > WINW || y < 0 || y > WINH)
		return ;
	texture->addr[(WINW*y) + x] = color;
}