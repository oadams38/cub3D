/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:13 by declerbo          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:28 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Ajoute une ligne au tableau tab */
int	append_line_to_tab(char ***tab, char *line)
{
	int		i;
	char	**nw_tab;

	nw_tab = malloc(sizeof(char *) * (ft_get_table_size(*tab) + 2));
	if (!nw_tab)
		return (1);
	i = 0;
	while (*tab && (*tab)[i])
	{
		nw_tab[i] = (*tab)[i];
		i++;
	}
	nw_tab[i++] = line;
	nw_tab[i] = NULL;
	free(*tab);
	*tab = nw_tab;
	return (0);
}

/* alloue un tableau de longueur width et hauteur height */
int	**allocate_map(int width, int height)
{
	int	**map_int;
	int	i;

	map_int = malloc(sizeof(int *) * (height + 1));
	if (!map_int)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_int[i] = malloc(sizeof(int) * width);
		if (!map_int[i])
		{
			while (--i >= 0)
				free(map_int[i]);
			return (free(map_int), NULL);
		}
		i++;
	}
	map_int[i] = NULL;
	return (map_int);
}

/* Renvoie la taille de la ligne la plus longue d'un tableau */
static int	max_len(char **tab)
{
	int	i;
	int	ln_max;

	i = 0;
	ln_max = 0;
	while (tab && tab[i])
	{
		if ((int)ft_strlen(tab[i]) > ln_max)
			ln_max = ft_strlen(tab[i]);
		i++;
	}
	return (ln_max);
}

static int	deal_new_player(t_data *data, char **map, int i, int j)
{
	if (data->p->pos.x != -1)
		return (err_mngmt(data, 1, NULL, ERR_MULTIPLE_START));
	init_player_values(data->p, j, i, map[i][j]);
	map[i][j] = '0';
	return (SUCCESS);
}

/* Transforme un tableau char en tableau int (terminée par NULL)*/
int	map_atoi(t_data *data, char **map_char)
{
	int	i;
	int	j;

	data->map_line_len = max_len(map_char);
	data->map = allocate_map(data->map_line_len, ft_get_table_size(map_char));
	if (!data->map)
		return (err_mngmt(data, 1, NULL, ERR_MALLOC));
	i = -1;
	while (map_char[++i])
	{
		j = -1;
		while (map_char[i][++j])
		{
			if (map_char[i][j] == ' ')
				map_char[i][j] = '2';
			else if (map_char[i][j] != '1' && map_char[i][j] != '0'
				&& deal_new_player(data, map_char, i, j))
				return (FAIL);
			data->map[i][j] = map_char[i][j] - '0';
		}
		while (j < data->map_line_len)
			data->map[i][j++] = 2;
	}
	return (SUCCESS);
}
