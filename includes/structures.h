/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:18:54 by oladams           #+#    #+#             */
/*   Updated: 2024/03/25 12:32:54 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vector
{
	float	y;
	float	x;
}	t_vector;

typedef struct s_img
{
	void	*id;
	char	*img_char;
	int		*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_ray
{
	t_vector	dir;
	int			wall_height;
	int			wall_height_clip;
	t_img		*wall_texture;
	float		wall_intersection;
}	t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_ray		*rays;
	float		move_speed;
	float		rotation_speed;
}	t_player;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		bits_per_pix;
	int		bytes_per_line;
	int		endian;
}	t_window;

typedef struct s_data
{
	t_window	*win;
	t_player	*p;
	char		*paths[4];
	int			back[2];
	t_img		*walls;
	int			**map;
	int			map_line_len;
	int			error;
	int			mouse_pos_x;
}	t_data;

typedef struct s_dda
{
	t_vector	delta_dist;
	t_vector	side_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	float		plane_wall_dist;
	int			hit;
	int			side;
	t_ray		*ray;
}	t_dda;

#endif