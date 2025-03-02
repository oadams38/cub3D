/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:40:02 by oladams           #+#    #+#             */
/*   Updated: 2024/03/25 12:30:04 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	end_minilib(t_data *data)
{
	if (!data->win->mlx_ptr || !data->win->img.id)
		return (FAIL);
	mlx_destroy_image(data->win->mlx_ptr, data->win->img.id);
	if (!data->win->win_ptr)
		return (FAIL);
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	free(data->win);
	data->win = NULL;
	clear_data(data);
	exit(data->error);
	return (1);
}

int	mouse_event(int x, int y, t_data *data)
{
	(void)y;
	if (data->mouse_pos_x != IMPOSSIBLE_VALUE)
		rotate(data, data->p, (x - data->mouse_pos_x) / 2);
	data->mouse_pos_x = x;
	return (0);
}

static void	change_speed(t_data *data, float factor)
{
	data->p->rotation_speed *= factor;
	data->p->move_speed *= factor;
	if (data->p->rotation_speed >= 1)
		data->p->rotation_speed = 0.999999;
	if (data->p->move_speed >= 1)
		data->p->move_speed = 0.999999;
}

int	key_event(int key, t_data *data)
{
	if (key == KEY_ESC)
		end_minilib(data);
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		move(data, key);
	else if (key == KEY_LEFT)
		rotate(data, data->p, -1);
	else if (key == KEY_RIGHT)
		rotate(data, data->p, 1);
	else if (key == KEY_PLUS)
		change_speed(data, 1.1);
	else if (key == KEY_MINUS)
		change_speed(data, 0.9);
	return (key);
}
