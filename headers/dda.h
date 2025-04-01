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

void    get_remains(float *dir, float *remains ,float *crds, int *crds_int);
#endif
