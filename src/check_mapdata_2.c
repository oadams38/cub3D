#include "../inc/cub3D.h"

int		check_floor_ceil(int *colour, char *subject)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (!(colour[i] >= 0 && colour[i] <= 255))
			return (wrong_rgb_error(subject));
	}
	return (1);
}

int		check_resolution(int *resolution)
{
	if (resolution[0] < 50 || resolution[1] < 40)
		return (resolution_error());
	return (1);
}

int		check_path(char *path, char *subject)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (wrong_path_error(path, subject));
	close(fd);
	return (1);
}