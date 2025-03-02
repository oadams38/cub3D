/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:00:44 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:33 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_colour(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	set_ray_dir_values(t_player *p)
{
	int		i;
	float	camera;

	i = 0;
	while (i < W_WIDTH)
	{
		camera = 2 * (float)(i) / (float)(W_WIDTH) - (float)(1);
		p->rays[i].dir = v_add(p->dir, v_factor(p->plane, camera));
		i++;
	}
}
