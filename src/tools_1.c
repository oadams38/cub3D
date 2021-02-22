#include "../inc/cub3D.h"

int		*pint(int n)
{
	int		*pint;

	pint = calloc(1, sizeof(pint));
	*pint = n;
	return (pint);
}