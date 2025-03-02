/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:31:17 by declerbo          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:27 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	choose_texture(char *texture_name)
{
	int		i;
	char	*texture[6];

	texture[0] = "NO";
	texture[1] = "SO";
	texture[2] = "WE";
	texture[3] = "EA";
	texture[4] = "F";
	texture[5] = "C";
	i = -1;
	while (++i < 6)
	{
		if (!ft_strncmp(texture[i], texture_name, -1))
			return (i);
	}
	return (-1);
}

static void	floor_n_ceiling(t_data *data, int da_index, char **tabline)
{
	char	**tmp;

	da_index = da_index % 4;
	if (data->back[da_index]
		&& err_mngmt(data, 1, tabline[0], ": duplicate texture\n"))
		return ;
	tmp = ft_split(tabline[1], ",");
	if (!tmp)
		err_mngmt(data, 1, NULL, ERR_MALLOC);
	else if (check_rgb_type(tmp))
	{
		free_char_tab(&tmp);
		err_mngmt(data, 1, tabline[1], ": bad int\n");
	}
	else
		data->back[da_index] = ft_atoi(tmp[0]) << 16
			| ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]);
	free_char_tab(&tmp);
}

static void	tabline_machine(t_data *data, char **tabline, char *line)
{
	int		da_index;

	if (ft_get_table_size(tabline) != 2
		&& err_mngmt(data, 1, line, ": incorrect data shape\n"))
		return ;
	da_index = choose_texture(tabline[0]);
	if (da_index < 0)
		err_mngmt(data, 1, tabline[0], ": unknow texture\n");
	else if (da_index < 4)
	{
		if (data->paths[da_index])
			err_mngmt(data, 1, tabline[0], ": duplicate texture\n");
		else
		{
			data->paths[da_index] = ft_strdup(tabline[1]);
			if (!data->paths[da_index])
				err_mngmt(data, 1, NULL, ERR_MALLOC);
		}
	}
	else
		floor_n_ceiling(data, da_index, tabline);
}

static char	*add_space(char *line)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (ft_strlen(line) + 2));
	if (!new_line && my_free((void **)&line))
		return (NULL);
	new_line[0] = line[0];
	i = 1;
	if (is_dir(line))
	{
		new_line[1] = line[1];
		new_line[2] = ' ';
		i = 2;
	}
	else
		new_line[1] = ' ';
	while (line[i])
	{
		new_line[i + 1] = line[i];
		i++;
	}
	new_line[i + 1] = '\0';
	free(line);
	return (new_line);
}

void	set_texture(t_data *data, int fd)
{
	char		*line;
	char		**tabline;
	int			count_line;

	count_line = 0;
	while (!data->error && count_line < 6)
	{
		line = mget_next_line(fd);
		if (!line && err_mngmt(data, 1, NULL, ERR_MALLOC))
			return ;
		if ((is_dir(line) && line[2] != ' ') || (is_fc(line) && line[1] != ' '))
		{
			line = add_space(line);
			if (!line && err_mngmt(data, 1, NULL, ERR_MALLOC))
				return ;
		}
		tabline = ft_split(line, " ");
		if (!tabline)
			err_mngmt(data, 1, NULL, ERR_MALLOC);
		else if (*tabline && ++count_line)
			tabline_machine(data, tabline, line);
		free(line);
		free_char_tab(&tabline);
	}
}
