#ifndef CUB3D_H
# define CUB3D_H

# include "../inc/libft.h"
# include "../inc/libft_bonus.h"
# include "../inc/mlx.h"
# include "../inc/mlx_int.h"
# include <stdio.h>
# include <math.h>
# include <errno.h>

# define FOV 60

typedef struct s_map t_map;

typedef struct 	s_mapdata
{
	int				resolution[2];
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	char			*path_sprite;
	int				floor[3];
	int				ceiling[3];
	char			*str_map;
	t_map			*map;
}				t_mapdata;

typedef struct s_map
{
	int				**grid;
	int				height;
	int				width;
	char			*name;
	t_mapdata		*mapdata;
}				t_map;



typedef struct	s_pathfinder
{
	int					x;
	int					y;
	int					steps;
	double				distance;
	double				cost;
	int					all_discovered;
	struct s_pathfinder	*next;
}				t_pathfinder;

t_mapdata  	*get_map_data(char *argv);
int			*ft_strtoitab(char *str);
int			check_mapdata(t_mapdata *mapdata);
void		print_map(int **map, t_pathfinder **path);
void        play_level(char *map);

//	errors
void		*malloc_error();
int			malloc_error_int();
void		*duplicate_or_missing_param_error(char *param);
void		*wrong_map_char();
void		*astar_search_malloc_fail(t_pathfinder **head);
int			walls_not_closed_error();
int			missing_entry_error(char *missing_entry);
int			missing_player_error();
void		*missing_map_error();
int			wrong_rgb_error(char *subject);
int			resolution_error();
int			wrong_path_error(char *path, char *subject);

int			find_player_border_path(int **mapdata, int y, int x);
void		free_t_pathfinder(t_pathfinder **head);

//	check_mapdata_2
int			check_floor_ceil(int *colour, char *subject);
int			check_resolution(int *resolution);
int			check_path(char *path, char *subject);


int			start_minilibx();

int			*pint(int n);

#endif