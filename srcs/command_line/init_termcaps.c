/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/02 15:09:40 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/ioctl.h>

t_read			*get_size(t_read *data)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		ft_putstr("ioctl error");
	data->ws_col = size.ws_col;
	data->ws_li = size.ws_row;
	return (data);
}

void			init_termcaps(void)
{
	char		*sh;
	char		bp[1024];

	if (!(sh = getenv("TERM")))
		EXIT_FAILURE ;
	if (tgetent(bp, sh) != 1)
		EXIT_FAILURE ;
	tgetstr("cm", NULL);
}
