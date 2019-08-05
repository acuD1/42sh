/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:37:41 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/05 19:20:48 by fcatusse         ###   ########.fr       */
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

void		load_subshell_quote(t_read *line)
{
	char	buff[READ_SIZE];

	insert_newline_in_buff(line);
	line->found = 0;
	while (TRUE)
	{
		ft_putstr("> ");
		while (read(STDIN_FILENO, buff, READ_SIZE))
		{
			if (check_caps(buff, line) == TRUE)
			{
				(buff[0] == '\'') ? line->found = 1 : 0;
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
