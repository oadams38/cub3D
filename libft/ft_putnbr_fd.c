/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:58:14 by oladams           #+#    #+#             */
/*   Updated: 2023/12/06 17:30:21 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		if (write(fd, "-2147483648", 11) < 0)
			return (-1);
		return (0);
	}
	if (n < 0)
	{
		if (write(fd, "-", 1) < 0)
			return (-1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	return (write(fd, &c, 1));
}
