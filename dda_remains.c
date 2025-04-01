#include "headers/dda.h"
void    get_remains(float *dir, float *remains ,float *crds, int *crds_int)
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
