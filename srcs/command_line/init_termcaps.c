/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/02 15:51:32 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/ioctl.h>

t_read			*get_size(t_read *data)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == FAILURE)
		ft_putstr("ioctl error"); //call an error fct
	data->ws_col = size.ws_col;
	data->ws_li = size.ws_row;
	return (data);
}

void			init_termcaps(void)
{
	char		*sh;
	char		bp[1024];

	if (!(sh = getenv("TERM")))
	{
		// Display error msg
		EXIT_FAILURE ;
	}
	if (tgetent(bp, sh) == FAILURE)
	{
		// Display error msg
		EXIT_FAILURE ;
	}
}
