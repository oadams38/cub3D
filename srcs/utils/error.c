/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:37:49 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:23 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	err_mngmt(t_data *data, int error, char *str1, char *str2)
{
	if (data && !data->error)
		data->error = error;
	write(2, "Error: ", 7);
	while (str1 && *str1)
		write(2, str1++, 1);
	while (str2 && *str2)
		write(2, str2++, 1);
	return (error);
}
