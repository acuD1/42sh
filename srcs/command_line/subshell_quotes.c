/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:28:32 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/09 14:39:43 by fcatusse         ###   ########.fr       */
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

uint8_t		is_eof(char buff, char quote)
{
	if (buff == QUOTE && quote == QUOTE)
		return (TRUE);
	else if (buff == DQUOTE && quote == DQUOTE)
		return (TRUE);
	else if (buff == BQUOTE && quote == BQUOTE)
		return (TRUE);
	return (FALSE);
}

void		load_subshell_quote(char quote, t_read *line)
{
	char	buff[READ_SIZE];

	line->found = 0;
	insert_newline_in_buff(line);
	while (TRUE)
	{
		(quote == DQUOTE) ? ft_putstr("dquote> ") : ft_putstr("> ");
		while (read(STDIN_FILENO, buff, READ_SIZE))
		{
			if (is_eof(buff[0], quote) == TRUE)
				line->found = 1;
			if (check_caps(buff, line) == TRUE)
				continue ;
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
