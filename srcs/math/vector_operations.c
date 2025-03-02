/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:11:17 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:55:30 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_vector	v_add(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vector	v_sub(t_vector a, t_vector b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vector	v_factor(t_vector a, float factor)
{
	a.x *= factor;
	a.y *= factor;
	return (a);
}
