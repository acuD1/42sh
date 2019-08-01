/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/01 13:30:23 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"
# include <sys/ioctl.h>

t_read			*get_size(t_read *data)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, &size) < 0)
		ft_putstr("ioctl error");
	data->ws_col = size.ws_col;
	data->ws_li = size.ws_row;
	return (data);
}

t_termcaps		*init_termcaps(void)
{
	t_termcaps	*caps;
	char		*sh;
	char		bp[1024];

	caps = ft_memalloc(sizeof(*caps));
	if (!(sh = getenv("TERM")))
		EXIT_FAILURE ;
	if (tgetent(bp, sh) != 1)
		EXIT_FAILURE ;
	caps->cm = tgetstr("cm", NULL);
	return (caps);
}
