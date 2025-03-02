/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:28:15 by declerbo          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:28 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Renvoi 0 si la ligne ne contient que des char valide, -1 autrement */
static int	mapline_approved(char *line)
{
	int		i;
	int		j;
	char	*char_approved;

	char_approved = " 01NSWE";
	i = 0;
	while (line && line[i])
	{
		j = 0;
		while (char_approved[j] && line[i] != char_approved[j])
			j++;
		if (!char_approved[j])
			return (1);
		i++;
	}
	return (0);
}

static char	*jump_line(int fd)
{
	char	*line;

	line = mget_next_line(fd);
	while (line && !*line)
	{
		free(line);
		line = mget_next_line(fd);
	}
	return (line);
}

static void	fill_char_map(t_data *data, char *line, char ***map_char, int fd)
{
	while (!data->error && line)
	{
		if (!*line)
			err_mngmt(data, 1, NULL, "Empty line\n");
		else if (append_line_to_tab(map_char, line))
		{
			free(line);
			err_mngmt(data, 1, NULL, ERR_MALLOC);
		}
		else if (mapline_approved(line))
			err_mngmt(data, 1, line, " has a forbidden char\n");
		if (!data->error)
			line = mget_next_line(fd);
	}
}

static int	valid_map(t_data *data, char **map_char)
{
	int	i;
	int	j;

	i = -1;
	while (map_char[++i])
	{
		j = -1;
		while (map_char[i][++j])
		{
			if ((!i || i == ft_get_table_size(map_char) - 1 || !j
					|| j == (int)ft_strlen(map_char[i]) - 1)
				&& map_char[i][j] == '0')
				return (err_mngmt(data, 1, NULL, "invalid map\n"));
			if (map_char[i][j] == '0' && (map_char[i + 1][j] == ' '
					|| map_char[i - 1][j] == ' '
					|| map_char[i][j + 1] == ' '
					|| map_char[i][j - 1] == ' '))
				return (err_mngmt(data, 1, NULL, "invalid map\n"));
		}
	}
	return (0);
}

void	set_map(t_data *data, int fd)
{
	char	**map_char;
	char	*line;

	line = jump_line(fd);
	if (!line)
		err_mngmt(data, 1, NULL, "No map found\n");
	else
	{
		map_char = NULL;
		fill_char_map(data, line, &map_char, fd);
		if (!data->error && !valid_map(data, map_char))
			map_atoi(data, map_char);
		free_char_tab(&map_char);
	}
}
