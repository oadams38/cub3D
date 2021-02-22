#include "../inc/cub3D.h"

static int		check_closed_walls(int **map)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (map[y] && map[y][x] != -1 && map[y][x] < 'E')
	{
		while (map[y][x] != -1 && map[y][x] < 'E')
			x++;
		if (map[y][x] >= 'E')
			break;
		x = 0;
		y++;
	}
	if (find_player_border_path(map, y, x) != 0)
		return (0);
	return (1);
}

int		check_struct_content(t_mapdata *mapdata)
{
	if (check_floor_ceil(mapdata->ceiling, "ceiling") 
		&& check_floor_ceil(mapdata->floor, "floor")
		&& check_path(mapdata->path_ea, "east wall texture")
		&& check_path(mapdata->path_we, "west wall texture")
		&& check_path(mapdata->path_no, "north wall texture")
		&& check_path(mapdata->path_so, "south wall texture")
		&& check_path(mapdata->path_sprite, "sprite texture")
		&& check_resolution(mapdata->resolution))
		return (1);
	return (0);
}

static int		player_found(int **map)
{
	int		y;
	int		x;
	int		c;

	y = 0;
	if (!map)
		return (0);
	while (map[y])
	{
		x = -1;
		while (map[y][++x] != -1)
		{
			c = map[y][x];
			if (c == 'E' || c == 'W' || c == 'N' || c == 'S')
				return (1);
		}
		y++;
	}
	return (0);
}

int		check_mapdata(t_mapdata *mapdata)
{
	if (!check_struct_content(mapdata))
	 	return (0);
	if (!player_found(mapdata->map->grid))
		return (missing_player_error());
	if (!check_closed_walls(mapdata->map->grid))
		return (walls_not_closed_error());
	return (1);
}