/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:42 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/02 16:21:42 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

void		goto_prompt(t_read *line)
{
	while (line->x > line->prompt_len)
	{
		line->width--;
		move_left(line->buffer, line);
	}
	tputs(tgetstr("ce", NULL), 1, my_outc);
}

t_read		*display_prompt(t_read *term)
{
	char	path[BUFF_SIZE + 1];

	getcwd(path, BUFF_SIZE);
	term->prompt = ft_strdup(ft_strrchr(path, '/'));
	term->prompt_len = ft_strlen(term->prompt) + 6;
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term = get_size(term);
	//term->line = ft_memalloc(2048);
	//"\033[1;35;195m"
	dprintf(STDOUT_FILENO, "%s<< %s >>%s ", C_C, term->prompt + 1, C_X);
	return (term);
}
