/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:14:52 by oladams           #+#    #+#             */
/*   Updated: 2024/03/18 12:43:25 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

//function status code
# define FAIL 1
# define SUCCESS 0

//error messages
# define ERR_MALLOC	"malloc() failed\n"
# define ERR_OPEN	"open() failed\n"
# define ERR_CLOSE	"close() failed\n"
# define ERR_TEXTURE ""
# define ERR_MULTIPLE_START	"More than 1 start position\n"

//window management
# define W_HEIGHT 512
# define W_WIDTH 512

//map
# define VOID 0
# define WALL 1

// texture index
# define NO	0
# define SO	1
# define WE	2
# define EA	3

// back index
# define F	0
# define C	1

//keys
# define KEY_W		13
# define KEY_S		1
# define KEY_A		0
# define KEY_D		2
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_ESC	53
# define KEY_PLUS	69
# define KEY_MINUS	78

//minilibx
# define ON_KEYDOWN	2
# define ON_DESTROY	17

#endif