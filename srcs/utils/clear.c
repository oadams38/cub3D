/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:17:50 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:22 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_t_player(t_player **player)
{
	free((*player)->rays);
	free(*player);
	*player = NULL;
}

void	free_t_img(t_img **img)
{
	free((*img)->img);
	free(*img);
	*img = NULL;
}

void	clear_data(t_data *data)
{
	int	i;

	if (data->win)
		end_minilib(data);
	if (data->p)
		free_t_player(&(data->p));
	if (data->walls)
		free(data->walls);
	if (data->map)
		free_int_tab(&(data->map));
	i = 0;
	while (i < 4 && data->paths[i])
	{
		free(data->paths[i]);
		data->paths[i] = NULL;
		i++;
	}
}
