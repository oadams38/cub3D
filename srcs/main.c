/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:34:13 by oladams           #+#    #+#             */
/*   Updated: 2024/03/15 14:11:32 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (err_mngmt(NULL, 1, NULL,
				"Bad argument number (hint: you need 1)\n"));
	(init_data(&data) || set_data(&data, argv[1]) || loop(&data));
	clear_data(&data);
	return (data.error);
}
