/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:37:41 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/04 22:35:03 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		display_subprompt(t_read *line)
{
	ft_putstr("> ");
	line->prompt_len = 2;
	line->x = line->prompt_len;
	line->y = 0;
}

/*
** ToDo: remove quotes in line->buffer but save before with quotes in history...
*/

void		load_subshell_quote(t_read *line)
{
	char	buff[READ_SIZE];
	int	buf_index;

	line->x_index = 2;
	line->width = 2;
	while (1)
	{
		//ft_bzero(line->buffer, line->width);
		display_subprompt(line);
		while (read(STDIN_FILENO, buff, READ_SIZE))
		{
			if (check_caps(buff, line) == TRUE)
				continue ;
			if (!ft_strcmp(buff, "'"))
				break ;
			else
			{
				buf_index = line->x_index - line->prompt_len;
				line->width++;
				line->x_index++;
				line->buffer[buf_index] = '\n';
				break ;
			}
		}
		if (ft_strchr(line->buffer, '\''))
			break ;
	}
}
