/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/03 18:53:38 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		search_in_history(t_read *line)
{
	char	buff[READ_SIZE + 1];
	char	buff_tmp[BUFF_SIZE];
	t_lst	*history;
	int	i;

	i = -1;
	history = line->history;
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		xtputs(xtgetstr("cr", NULL), 1, my_outc);
		xtputs(xtgetstr("ce", NULL), 1, my_outc);
		if (*buff == NEW_LINE)
		{
			ft_strcpy(line->buffer, buff_tmp);
			return ;
		}
		buff_tmp[++i] = *buff;
		dprintf(STDIN_FILENO, "(reverse-i-search)`%s':", buff_tmp);
		while (history)
		{
			if (ft_strstr(history->data, buff_tmp) != 0)
			{
				dprintf(STDIN_FILENO, " %s", history->data);
				break ;
			}
			history = history->next;
		}
	}
}

void		resharper(t_read **line)
{
	goto_prompt(*line);
	xtputs(xtgetstr("cr", NULL), 1, my_outc);
	xtputs(xtgetstr("ce", NULL), 1, my_outc);
	dprintf(STDIN_FILENO, "(reverse-i-search)`':");
	search_in_history(*line);
	display_prompt(*line);
	dprintf(STDIN_FILENO, "%s\n", (*line)->buffer);
}
