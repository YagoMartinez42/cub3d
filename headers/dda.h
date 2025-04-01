#ifndef DDA_H
# define DDA_H
# include "cub3d.h"

typedef struct s_dda
{
    float   crds[2];
    float   costs[2];
    float   remains[2];
    int     crds_int[2];
}               t_dda;

void    get_remains(float *dir, float *remains ,float *crds, int *crds_int);
#endif
