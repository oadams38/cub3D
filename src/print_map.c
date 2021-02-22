#include "../inc/cub3D.h"

int		**remove_path(int **map)
{
	int		y;
	int		x;
	int		c;

	if (!map)
		return (NULL);
	y = 0;
	while (map[y])
	{
		x = 0;
		while ((c = map[y][x]) != -1)
		{
			if (!(c <= 10 || c == 'E' || c == 'S' || c == 'W' || c == 'N'))
				map[y][x] = 0;
			x++;
		}
		y++;
	}
	return (map);
}

int		**fill_map(int **map, t_pathfinder **path)
{
	t_pathfinder	*tmp;

	if (!map || !path)
		return (NULL);
	tmp = *path;
	while (tmp)
	{
		map[tmp->y][tmp->x] = '~';
		tmp = tmp->next;
	}
	return (map);
}

void	print_map(int **map, t_pathfinder **path)
{
	size_t		y;
	size_t		x;
	int			c;

	if (path != NULL)
		map = fill_map(map, path);
	y = 0;
	if (!map || !*map)
		return ;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != -1)
		{
			c = map[y][x] <= 'E' ? map[y][x] + '0' : map[y][x];
			write(1, &c, 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	if (path != NULL)
		map = remove_path(map);
}