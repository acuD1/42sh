/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:42 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 12:02:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

int	my_outc(int c)
{
	write(0, &c, 1);
	return (0);
}

void		goto_prompt(t_read *line)
{
	while (line->x > line->prompt_len)
		move_left(line->buffer, line);
	tputs(tgetstr("ce", NULL), 1, my_outc);
}

t_read		*display_prompt(t_read *term)
{
	char	path[BUFF_SIZE + 1];

	if (term->prompt && term->line)
	{
		free(term->prompt);
		free(term->line);
	}
	getcwd(path, BUFF_SIZE);
	term->prompt = ft_strdup(ft_strrchr(path, '/'));
	term->prompt_len = ft_strlen(term->prompt) + 6;
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term = get_size(term);
	term->line = ft_memalloc(2048);
	my_printf("\033[1;35;195m");
	my_printf("<< %s >> ", term->prompt + 1);
	my_printf("\033[0m");
	return (term);
}
