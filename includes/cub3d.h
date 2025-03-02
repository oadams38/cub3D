/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:12:20 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:44:11 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "structures.h"
# include "macros.h"
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define COLOR_WALL 0x00FFFFFF
# define COLOR_FLOOR 0x00000000
# define COLOR_PLAYER 0x00FF0000
# define BLOC_SIZE 16
# define MAP_SIZE 8
# define PLAYER_SIZE 4
# define ON_MOUSEMOVE 6
# define IMPOSSIBLE_VALUE -1000000

//MATH
	//dda.c
void		init_dda(t_dda *dda, t_ray *ray, t_vector pos);
void		perform_dda(t_dda *dda, int **map, t_player *player);
void		get_texture_height(t_dda dda, t_ray *ray, t_data *data);
	//draw.c
void		draw_frame(t_data *data);
	//move.c
void		rotate(t_data *data, t_player *p, int factor);
void		move(t_data *data, int key);
	//vector_operations.c
t_vector	v_add(t_vector a, t_vector b);
t_vector	v_sub(t_vector a, t_vector b);
t_vector	v_factor(t_vector a, float factor);

//MINILIB
	//events.c
int			end_minilib(t_data *data);
int			key_event(int key, t_data *data);
int			mouse_event(int x, int y, t_data *param);
	//loop.c
int			loop(t_data *data);

//PARSING
	//parsing_utils.c
char		*mget_next_line(int fd);
int			is_fc(char *str);
int			is_dir(char *str);
int			check_rgb_type(char **tab);
	//parsing_map.c
int			append_line_to_tab(char ***tab, char *line);
int			**allocate_map(int width, int height);
int			map_atoi(t_data *data, char **map_char);
	//parsing_main.c
int			set_data(t_data *data, char *file_name);
void		set_texture(t_data *data, int fd);
void		set_map(t_data *data, int fd);

//UTILS
	//clear_utils.c
int			my_free(void **ptr);
void		free_int_tab(int ***tab);
void		free_char_tab(char ***tab);
	//clear.c
void		free_t_player(t_player **player);
void		free_t_img(t_img **img);
void		clear_data(t_data *data);
	//error.c
int			err_mngmt(t_data *data, int error, char *str1, char *str2);
	//init.c
void		init_player_values(t_player *player, float x, float y, char dir);
int			init_data(t_data *data);
int			load_textures(t_data *data);
	//utils.c
int			get_colour(int t, int r, int g, int b);
void		set_ray_dir_values(t_player *player);

//MAP
	//map_utils.c
void		pixel_put(t_data *data, int x, int y, int color);
int			ft_sizemap(int **map);
int			sgn(int m);
	//map_bresenham.c
void		add_mapdir(t_data *data);
	//map_main.c
void		add_map(t_data *data);
void		add_mapplayer(t_data *data);
void		add_mapdir(t_data *data);

#endif
