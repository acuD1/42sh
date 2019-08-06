/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:28:32 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/06 14:49:05 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		insert_newline_in_buff(t_read *line)
{
	int	buf_index;

	buf_index = line->x_index - line->prompt_len;
	if (line->found != 1)
	{
		line->buffer[buf_index] = '\n';
		line->width++;
		line->x_index++;
	}
}

void		load_subshell_quote(char quote, t_read *line)
{
	char	buff[READ_SIZE];

	insert_newline_in_buff(line);
	line->found = 0;
	while (TRUE)
	{
		(quote == DQUOTE) ? ft_putstr("dquote> ") : ft_putstr("> ");
		while (read(STDIN_FILENO, buff, READ_SIZE))
		{
			if (check_caps(buff, line) == TRUE)
			{
				(buff[0] == SINGLE_QUOTE && quote == SINGLE_QUOTE) ? line->found = 1 : 0;
				(buff[0] == DQUOTE && quote == DQUOTE) ? line->found = 1 : 0;
				continue ;
			}
			else
			{
				insert_newline_in_buff(line);
				break ;
			}
		}
		if (line->found == 1)
			return ;
	}
}
