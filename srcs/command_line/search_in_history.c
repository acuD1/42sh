/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/19 13:42:56 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*walking_history(char buff_tmp[BUFF_SIZE], t_read *line, t_lst **history)
{
	while (*history)
	{
		if (ft_strstr((*history)->content, buff_tmp))
		{
			xtputs(line->termcaps->cr, 1, my_outc);
			xtputs(line->termcaps->clr_end, 1, my_outc);
			dprintf(STDIN_FILENO, "(reverse-i-search)`%s':", buff_tmp);
			dprintf(STDIN_FILENO, " %s",(*history)->content);
			ft_strcpy(line->buffer, (*history)->content);
			if ((*history)->next)
				(*history) = (*history)->next;
			return ((*history)->content);
		}
		(*history) = (*history)->next;
	}
	return (NULL);
}

void		search_in_history(t_read *line)
{
	char	buff[READ_SIZE + 1];
	char	buff_tmp[BUFF_SIZE];
	int		i;
	t_lst	*history;

	history = line->history;
	i = -1;
	ft_bzero(buff_tmp, BUFF_SIZE);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (!is_print(*buff) && *buff != CTRL_R)
			return ;
		else if (is_print(*buff))
			buff_tmp[++i] = *buff;
		walking_history(buff_tmp, line, &history);
	}
}

void		research_mode(t_read **line)
{
	goto_prompt(*line);
	xtputs((*line)->termcaps->cr, 1, my_outc);
	xtputs((*line)->termcaps->clr_end, 1, my_outc);
	dprintf(STDIN_FILENO, "(reverse-i-search)`':");
	search_in_history(*line);
	xtputs((*line)->termcaps->cr, 1, my_outc);
	xtputs((*line)->termcaps->clr_end, 1, my_outc);
	display_prompt(*line);
	dprintf(STDIN_FILENO, "%s", (*line)->buffer);
	(*line)->x += ft_strlen((*line)->buffer);
	(*line)->width = (*line)->x;
	(*line)->x_index = (*line)->x;
}
