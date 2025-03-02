/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:47:07 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:31 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_mlx(t_window *win)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return (FAIL);
	win->win_ptr = mlx_new_window(win->mlx_ptr, W_WIDTH, W_HEIGHT,
			"Teissere'ACT");
	if (!win->win_ptr)
		return (FAIL);
	win->img.id = mlx_new_image(win->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!win->img.id)
		return (FAIL);
	win->img.img_char = mlx_get_data_addr(win->img.id, &(win->bits_per_pix),
			&(win->bytes_per_line), &(win->endian));
	if (!win->img.img_char)
		return (FAIL);
	win->img.img = (int *)(win->img.img_char);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.id, 0, 0);
	return (SUCCESS);
}

int	loop(t_data *data)
{
	if (init_mlx(data->win))
		return (err_mngmt(data, 1, NULL, "la mlx elle a pas marché\n"));
	if (load_textures(data))
		return (FAIL);
	draw_frame(data);
	mlx_hook(data->win->win_ptr, ON_KEYDOWN, 0, &key_event, data);
	mlx_hook(data->win->win_ptr, ON_MOUSEMOVE, 0, &mouse_event, data);
	mlx_hook(data->win->win_ptr, ON_DESTROY, 0, &end_minilib, data);
	mlx_loop(data->win->mlx_ptr);
	return (SUCCESS);
}
