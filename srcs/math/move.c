/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:01:43 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:33 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(t_data *data, t_player *p, int fact)
{
	float		tmp;
	float		rotation;

	rotation = fact * p->rotation_speed;
	tmp = p->dir.x;
	p->dir.x = p->dir.x * cos(rotation) - p->dir.y * sin(rotation);
	p->dir.y = tmp * sin(rotation) + p->dir.y * cos(rotation);
	tmp = p->plane.x;
	p->plane.x = p->plane.x * cos(rotation) - p->plane.y * sin(rotation);
	p->plane.y = tmp * sin(rotation) + p->plane.y * cos(rotation);
	set_ray_dir_values(p);
	draw_frame(data);
}

static t_vector	get_moving_vector(t_player *p, int key)
{
	t_vector	move;

	if (key == KEY_W)
		move = p->dir;
	else if (key == KEY_S)
		move = v_factor(p->dir, -1);
	else if (key == KEY_A)
	{
		move.x = p->dir.y;
		move.y = -p->dir.x;
	}
	else
	{
		move.x = -p->dir.y;
		move.y = p->dir.x;
	}
	move = v_factor(move, p->move_speed);
	return (move);
}

void	move(t_data *data, int key)
{
	t_player	*p;
	t_vector	move;

	p = data->p;
	move = get_moving_vector(p, key);
	if (data->map[(int)(p->pos.y + move.y)][(int)(p->pos.x + move.x)] != WALL)
	{
		p->pos.x += move.x;
		p->pos.y += move.y;
	}
	else if (data->map[(int)(p->pos.y + move.y)][(int)(p->pos.x)] != WALL)
		p->pos.y += move.y / 2;
	else if (data->map[(int)(p->pos.y)][(int)(p->pos.x + move.x)] != WALL)
		p->pos.x += move.x / 2;
	set_ray_dir_values(p);
	draw_frame(data);
}
