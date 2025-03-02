/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:28:34 by declerbo          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:25 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*mget_next_line(int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (str)
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

int	is_fc(char *str)
{
	if (str && (str[0] == 'C' || str[0] == 'F'))
		return (1);
	return (0);
}

int	is_dir(char *str)
{
	if (str && (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
			|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2)))
		return (2);
	return (0);
}

int	check_rgb_type(char **tab)
{
	int	i;
	int	j;

	if (ft_get_table_size(tab) != 3)
		return (1);
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (ft_isdigit(tab[i][j]))
			j++;
		if (tab[i][j] || ft_atoi(tab[i]) > 255)
			return (1);
		i++;
	}
	return (0);
}
