/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:18:28 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:15 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_start_end(t_ray *ray, int *draw_start, int *draw_end)
{
	*draw_start = -ray->wall_height_clip / 2 + W_HEIGHT / 2;
	*draw_end = ray->wall_height_clip / 2 + W_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= W_HEIGHT)
		*draw_end = W_HEIGHT - 1;
}

static void	floor_ceiling(t_data *data, int x, int draw_start, int draw_end)
{
	int	*img;
	int	i;

	img = (data->win->img.img);
	i = -1;
	while (++i < draw_start)
		img[i * W_WIDTH + x] = data->back[C];
	i = W_HEIGHT;
	while (--i > draw_end)
		img[i * W_WIDTH + x] = data->back[F];
}

static void	set_tex_point(t_vector *tex, t_ray *ray, t_dda dda, float *y_step)
{
	tex->x = ray->wall_intersection * (float)(ray->wall_texture->width);
	if ((dda.side == 0 && ray->dir.x > 0) || (dda.side == 1 && ray->dir.y < 0))
		tex->x = (float)(ray->wall_texture->width) - tex->x - (float)(1);
	tex->y = 0;
	if (ray->wall_height <= W_HEIGHT)
		*y_step = (float)(ray->wall_texture->height)
			/ (float)(ray->wall_height);
	else
	{
		tex->y = ((float)(ray->wall_texture->height) * (1 - (float)(W_HEIGHT)
					/ (float)(ray->wall_height))) / (float)(2);
		*y_step = ((float)(ray->wall_texture->height) * ((float)(W_HEIGHT)
					/ (float)(ray->wall_height)) - 1) / (float)(W_HEIGHT);
	}
}

static void	draw_column(t_data *data, t_dda dda, t_ray *ray, int x)
{
	int			draw_start;
	int			draw_end;
	t_vector	tex;
	float		y_step;
	int			*img;

	img = data->win->img.img;
	set_start_end(ray, &draw_start, &draw_end);
	floor_ceiling(data, x, draw_start, draw_end);
	set_tex_point(&tex, ray, dda, &y_step);
	while (draw_start < draw_end)
	{
		img[draw_start * W_WIDTH + x] = ray->wall_texture->img[
			ray->wall_texture->width * (int)(tex.y) + (int)(tex.x)];
		tex.y += y_step;
		draw_start++;
	}
}

void	draw_frame(t_data *data)
{
	t_player	*player;
	t_dda		dda;
	int			i;

	player = data->p;
	i = 0;
	while (i < W_WIDTH)
	{
		dda.ray = &(player->rays[i]);
		init_dda(&dda, dda.ray, player->pos);
		perform_dda(&dda, data->map, player);
		get_texture_height(dda, dda.ray, data);
		draw_column(data, dda, dda.ray, i);
		i++;
	}
	add_map(data);
	add_mapplayer(data);
	add_mapdir(data);
	mlx_put_image_to_window(data->win->mlx_ptr,
		data->win->win_ptr, data->win->img.id, 0, 0);
	ft_memset(data->win->img.img_char, 0,
		W_HEIGHT * W_WIDTH * (data->win->bits_per_pix / 8));
}
