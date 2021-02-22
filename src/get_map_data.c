#include "../inc/cub3D.h"



int		*str_to_inttab(char *line, size_t x)
{
	int		*row;
	size_t	i;
	
	if ((row = ft_calloc(x + 1, sizeof(row))) == NULL)
		return (malloc_error());
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			row[i] = 0;
		else if (ft_isalpha(line[i]))
			row[i] = (int)line[i];
		else if (ft_isdigit(line[i]))
			row[i] = (int)(line[i] - '0');
		else 
			return (wrong_map_char());
		i++;
	}
	while (i < x)
		row[i++] = 0;
	row[i] = -1;
	return (row);
}

int     **get_map(char **map, int start, int y)
{
	int		**matrix;
	size_t	x;

	if ((matrix = ft_calloc(y + 1, sizeof(matrix))) == NULL)
		return (malloc_error());
	matrix[y] = NULL;
	x = 0;
	while (y--)
		x = ft_strlen(map[y + start]) > x ? ft_strlen(map[y + start]) : x;
	while (map[++y + start] != NULL)
	{
		if ((matrix[y] = str_to_inttab(map[y + start], x)) == NULL)
			return (NULL);
	}
	return (matrix);
}

void	free_matrix(void *mat)
{
	int		y;
	int		**matrix;

	if (!mat)
		return ;
	y = 0;
	matrix = (int **)mat;
	while (matrix[y])
		free((void*)matrix[y++]);
	free((void*)matrix);
}

static int		line_to_struct(t_mapdata *ptr, char **tmp_t)
{
	int		i;

	i = -1;
    if (ft_strcmp(tmp_t[0], "NO") == 0 && !(ptr->path_no))
		ptr->path_no = ft_strcreate(tmp_t[1]);
	else if (ft_strcmp(tmp_t[0], "SO") == 0 && !(ptr->path_so))
		ptr->path_so = ft_strcreate(tmp_t[1]);
	else if (ft_strcmp(tmp_t[0], "WE") == 0 && !(ptr->path_we))
		ptr->path_we = ft_strcreate(tmp_t[1]);
	else if (ft_strcmp(tmp_t[0], "EA") == 0 && !(ptr->path_ea))
		ptr->path_ea = ft_strcreate(tmp_t[1]);
	else if (ft_strcmp(tmp_t[0], "S") == 0 && !(ptr->path_sprite))
		ptr->path_sprite = ft_strcreate(tmp_t[1]);
	else if (ft_strcmp(tmp_t[0], "R") == 0 && ptr->resolution[0] == -1)
		while(++i < 2)
			ptr->resolution[i] = ft_atoi(tmp_t[i + 1]);
	else if (ft_strcmp(tmp_t[0], "F") == 0 && ptr->floor[0] == -1)
		while(++i < 3)
			ptr->floor[i] = ft_atoi(tmp_t[i + 1]);
	else if (ft_strcmp(tmp_t[0], "C") == 0 && ptr->ceiling[0] == -1)
		while(++i < 3)
			ptr->ceiling[i] = ft_atoi(tmp_t[i + 1]);
	else
		return (0);
	return (1);
}

void  *tab_to_struct(char **lines, t_mapdata *ptr)
{
    int     i;
	int		y_map;
	char	**tmp_t;
    
    i = -1;
	//everything above the map
    while (lines[++i] != NULL && ft_atoi(lines[i]) == 0)
	{
		if (!(tmp_t = ft_splitset(lines[i], " ,\t")))
       		return (malloc_error());
        if (!(line_to_struct(ptr, tmp_t)))
		{
			ft_freetab(tmp_t);
			return (duplicate_or_missing_param_error(tmp_t[0]));
		}
		ft_freetab(tmp_t);
	}
	//the map
    if (lines[i] == NULL)
		return (missing_map_error());
	y_map = 0;
	while (lines[i + y_map] && ft_atoi(lines[i + y_map]) != 0)
		y_map++;
	ptr->map->grid = get_map(lines, i, y_map);
	return (NULL);
}

void		init_mapdata_struct(t_mapdata *ptr, t_map *map)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		ptr->ceiling[i] = -1;
		ptr->floor[i] = -1;
		if (i < 2)
			ptr->resolution[i] = -1;
	}
	ptr->path_ea = NULL;
	ptr->path_no = NULL;
	ptr->path_so = NULL;
	ptr->path_we = NULL;
	ptr->path_sprite = NULL;
	ptr->str_map = NULL;
	ptr->map = map;
	ptr->map->grid = NULL;
	ptr->map->height = -1;
	ptr->map->width = -1;
	ptr->map->name = NULL;
}

t_mapdata  *get_map_data(char *argv)
{
    char    *file;
    char    *tmp;
    char    **lines;
	t_mapdata	*ptr;
	t_map		*map;

	if (!(ptr = (t_mapdata *)malloc(sizeof(t_mapdata))))
		return (NULL);
    if ((file = ft_readfile(argv, 1000)) == NULL)
		return (NULL);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	init_mapdata_struct(ptr, map);
    tmp = ft_strtrim(file, " \n\t");
    lines = ft_splitset(tmp, "\n\r");
    tab_to_struct(lines, ptr);
    free((void*)tmp);
    free((void*)file);
    ft_freetab(lines);
    return (ptr);
}