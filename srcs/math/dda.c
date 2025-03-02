/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:39:48 by oladams           #+#    #+#             */
/*   Updated: 2024/03/25 12:28:54 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_steps(t_dda *dda, t_ray *ray, t_vector pos)
{
	if (ray->dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist.x = (pos.x - (floor(pos.x))) * dda->delta_dist.x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist.x = (floor(pos.x) + 1.0 - pos.x) * dda->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist.y = (pos.y - floor(pos.y)) * dda->delta_dist.y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist.y = (floor(pos.y) + 1.0 - pos.y) * dda->delta_dist.y;
	}
}

void	init_dda(t_dda *dda, t_ray *ray, t_vector pos)
{
	if (ray->dir.x == 0)
		dda->delta_dist.x = 1.40282347e+38F;
	else
		dda->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		dda->delta_dist.y = 1.40282347e+38F;
	else
		dda->delta_dist.y = fabs(1 / ray->dir.y);
	dda->map_x = (int)(pos.x);
	dda->map_y = (int)(pos.y);
	dda->hit = 0;
	set_steps(dda, ray, pos);
}

static void	get_intersection_distance(t_dda *dda, t_player *p)
{
	t_ray	*ray;

	ray = dda->ray;
	if (dda->side == 0)
	{
		dda->plane_wall_dist = dda->side_dist.x - dda->delta_dist.x;
		ray->wall_intersection = p->pos.y + dda->plane_wall_dist * ray->dir.y;
	}
	else
	{
		dda->plane_wall_dist = dda->side_dist.y - dda->delta_dist.y;
		ray->wall_intersection = p->pos.x + dda->plane_wall_dist * ray->dir.x;
	}
	ray->wall_intersection -= floor(ray->wall_intersection);
}

void	perform_dda(t_dda *dda, int **map, t_player *player)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map[dda->map_y][dda->map_x] != VOID)
			dda->hit = 1;
	}
	get_intersection_distance(dda, player);
}

void	get_texture_height(t_dda dda, t_ray *ray, t_data *data)
{
	float		h_factor;

	h_factor = 0.6;
	ray->wall_height = abs((int)((
					(float)(h_factor * W_HEIGHT)) / dda.plane_wall_dist));
	if (ray->wall_height == INT_MIN)
		ray->wall_height = INT_MAX;
	if (ray->wall_height > W_HEIGHT || ray->wall_height < 0)
		ray->wall_height_clip = W_HEIGHT;
	else
		ray->wall_height_clip = ray->wall_height;
	if (dda.side == 0 && ray->dir.x < 0)
		ray->wall_texture = &(data->walls[WE]);
	if (dda.side == 0 && ray->dir.x >= 0)
		ray->wall_texture = &(data->walls[EA]);
	if (dda.side == 1 && ray->dir.y < 0)
		ray->wall_texture = &(data->walls[NO]);
	if (dda.side == 1 && ray->dir.y >= 0)
		ray->wall_texture = &(data->walls[SO]);
}
