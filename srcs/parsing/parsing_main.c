/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:31:13 by declerbo          #+#    #+#             */
/*   Updated: 2024/03/25 12:58:34 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	approved_filename(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (i >= 4 && !ft_strncmp(".cub", &file_name[i - 4], 5))
		return (0);
	return (1);
}

int	set_data(t_data *data, char *file_name)
{
	int		fd;

	if (approved_filename(file_name))
		return (err_mngmt(data, 1, file_name, ": .cub needed\n"));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (err_mngmt(data, 1, NULL, ERR_OPEN));
	set_texture(data, fd);
	if (!data->error)
		set_map(data, fd);
	if (close(fd) == -1)
		return (err_mngmt(data, 1, NULL, ERR_CLOSE));
	return (data->error);
}
