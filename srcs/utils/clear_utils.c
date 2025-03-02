/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:39:55 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:20 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_char_tab(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab) && (*tab)[i])
		free((*tab)[i++]);
	free((*tab));
	*tab = NULL;
}

int	my_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}

void	free_int_tab(int ***tab)
{
	int	i;

	if (!*tab)
		return ;
	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}
