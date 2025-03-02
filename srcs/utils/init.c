/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:34:48 by oladams           #+#    #+#             */
/*   Updated: 2024/03/25 12:28:31 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_values(t_player *player, float x, float y, char dir)
{
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	player->dir.x = 0;
	player->dir.y = 0;
	if (dir == 'N')
		player->dir.y = -1;
	else if (dir == 'S')
		player->dir.y = 1;
	else if (dir == 'W')
		player->dir.x = -1;
	else
		player->dir.x = 1;
	player->plane.y = player->dir.x;
	player->plane.x = -player->dir.y;
	player->move_speed = 0.05;
	player->rotation_speed = 0.03;
	set_ray_dir_values(player);
}

int	load_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->walls[i].id = mlx_xpm_file_to_image(data->win->mlx_ptr,
				data->paths[i], &(data->walls[i].width),
				&(data->walls[i].height));
		if (!(data->walls[i].id))
			return (err_mngmt(data, 1, data->paths[i], ": can't open file\n"));
		data->walls[i].img_char = mlx_get_data_addr(data->walls[i].id,
				&(data->win->bits_per_pix),
				&(data->win->bytes_per_line),
				&(data->win->endian));
		data->walls[i].img = (int *)data->walls[i].img_char;
		i++;
	}
	return (SUCCESS);
}

static void	set_null(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->paths[i] = NULL;
	data->map = NULL;
	data->error = 0;
	data->p = NULL;
	data->win = NULL;
	data->walls = NULL;
}

int	init_data(t_data *data)
{
	set_null(data);
	data->mouse_pos_x = IMPOSSIBLE_VALUE;
	data->win = malloc(sizeof(t_window));
	if (data->win)
	{
		data->win->mlx_ptr = NULL;
		data->win->win_ptr = NULL;
		data->win->bytes_per_line = 4 * W_WIDTH;
		data->win->bits_per_pix = 8;
		data->win->endian = 1;
	}
	data->p = malloc(sizeof(t_player));
	if (data->p)
	{
		data->p->rays = NULL;
		data->p->rays = malloc(sizeof(t_ray) * W_WIDTH);
		data->p->pos.x = -1;
	}
	data->walls = malloc(sizeof(t_img) * 4);
	if (!data->p || !data->win || !data->p->rays || !data->walls)
		return (err_mngmt(data, 1, NULL, ERR_MALLOC));
	return (SUCCESS);
}
