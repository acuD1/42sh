/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:13:27 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/08 20:05:38 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

#include <fcntl.h>
static void		debuga(const char *path, int width, int i)
{
	int			fd;

	fd = open(path, O_WRONLY);
	ft_dprintf(fd, "buff_index[%d] width[%d]\n\n", i, width);
}

/* ssize_t		get_width_last_line(t_read *term) */
/* { */
/* 	ssize_t	buff_index; */
/* 	ssize_t	width; */
/*  */
/* 	width = 0; */
/* 	buff_index = term->x_index - (ssize_t)term->prompt_len - 1; */
/* 	while (buff_index-- > 0 && width < (term->ws_col - 1)) */
/* 	{ */
/* 		debuga("/dev/pts/2", width, buff_index); */
/* 		if (term->buffer[buff_index] == '\n') */
/* 			break ; */
/* 		width++; */
/* 	} */
/* 	if (term->y == 1) */
/* 		width += term->prompt_len; */
/* 	if (width == term->ws_col) */
/* 	{ */
/* 		width--; */
/* 		term->x_index--; */
/* 	} */
/* 	return (width); */
/* } */

ssize_t		get_width_last_line(t_read *term)
{
	ssize_t	buff_index;
	ssize_t	width;
	ssize_t	x;

	width = 0;
	x = term->x;
	buff_index = term->x_index - (ssize_t)term->prompt_len;
	if ((buff_index > 0) && term->buffer[buff_index - 1] == NEW_LINE[0])
		buff_index--;
	while (buff_index-- > 0)
	{
		if (term->buffer[buff_index] == NEW_LINE[0])
			break ;
		else if (x == 0 && !ft_strchr(term->buffer, NEW_LINE[0]))
			return (term->ws_col - 1);
		x--;
		width++;
	}
	/* if (width > term->ws_col) */
	/* 	width -= term->ws_col; */
	if (term->y == 1)
		width += term->prompt_len;
	debuga("/dev/pts/2", buff_index, width);
	return (width);
}

ssize_t		get_width_current_line(t_read *term)
{
	ssize_t	buff_index;
	ssize_t	width;
	ssize_t	x;

	width = 0;
	x = term->x;
	buff_index = term->x_index - (ssize_t)term->prompt_len;
	while (buff_index < (ssize_t)ft_strlen(term->buffer))
	{
		if (term->buffer[buff_index] == '\n' || x == (term->ws_col - 1))
			break ;
		width++;
		x++;
		buff_index++;
	}
	width += term->x;
	return (width);
}

u_int64_t	get_mask(const char *buff)
{
	u_int16_t	i;
	u_int16_t	shift;
	u_int64_t	value;
	u_int64_t	tmp;

	i = 0;
	tmp = 0;
	value = 0;
	shift = 56;
	while (i < 8 && buff && buff[i])
	{
		value = (u_int64_t)buff[i];
		value <<= shift;
		tmp |= value;
		shift -= 8;
		i++;
	}
	return (tmp);
}
