/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/09 18:06:38 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*walking_history(char buff_tmp[BUFF_SIZE], t_read *line, t_lst **history)
{
	while ((*history)->next)
	{
		if (ft_strstr((*history)->content, buff_tmp))
		{
			xtputs(line->tcaps[LEFT_MARGIN], 1, my_outc);
			xtputs(line->tcaps[CLR_LINES], 1, my_outc);
			dprintf(STDIN_FILENO, "(reverse-i-search)`%s':", buff_tmp);
			dprintf(STDIN_FILENO, " %s", (char *)(*history)->content);
			ft_strcpy(line->buffer, (*history)->content);
			if ((*history)->next)
				(*history) = (*history)->next;
			return ((*history)->content);
		}
		(*history) = (*history)->next;
	}
	return (NULL);
}

void			search_in_history(t_read *line)
{
	char		buff[READ_SIZE + 1];
	char		buff_tmp[BUFF_SIZE];
	int		i;
	t_lst		*history;
	uint64_t 	value;

	history = line->history;
	i = -1;
	ft_bzero(buff_tmp, BUFF_SIZE);
	ft_bzero(buff, READ_SIZE + 1);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (!is_print(*buff) && value != CTRL_R)
			return ;
		else if (is_print(*buff))
			buff_tmp[++i] = *buff;
		walking_history(buff_tmp, line, &history);
	}
}

void		research_mode(t_read *line)
{
	goto_prompt(line);
	xtputs(line->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(line->tcaps[CLR_LINES], 1, my_outc);
	dprintf(STDIN_FILENO, "(reverse-i-search)`':");
	search_in_history(line);
	xtputs(line->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(line->tcaps[CLR_LINES], 1, my_outc);
	display_prompt(line);
	ft_dprintf(STDIN_FILENO, "%s", line->buffer);
	line->x += ft_strlen(line->buffer);
	line->width = line->x;
	line->x_index = line->x;
}
