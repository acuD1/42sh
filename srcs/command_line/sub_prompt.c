/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/14 16:57:38 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		insert_newline_in_buff(t_read *line)
{
	int		buff_index;

	buff_index = line->x_index - line->prompt_len;
	if (line->found != 1)
	{
		line->buffer[buff_index] = NEW_LINE;
		line->width++;
		line->x = 0;
		line->y++;
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

void		load_subprompt(char quote, t_read *line)
{
	char	buff[READ_SIZE];

	line->found = 0;
	insert_newline_in_buff(line);
	ft_bzero(buff, READ_SIZE);
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
