/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:49:49 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/19 16:39:44 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	replace_cursor(t_read *term, const char buff_tmp)
{
	ssize_t		i;

	i = (ssize_t)ft_strlen(term->buffer) - 1;
	while (i >= 0)
	{
		xtputs(term->tcaps[KEY_LEFT], 1, my_outc);
		if (term->buffer[i] == buff_tmp)
			break ;
		i--;
	}
}

void		goto_reverse(t_read *term, const char *buff_tmp)
{
	display_prompt(term);
	xtputs(term->tcaps[RESTORE_CR], 1, my_outc);
	xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
	if (term->search == SEARCH_SUCCESS)
		ft_dprintf(STDOUT_FILENO, "(reverse-i-search)`%s': ", buff_tmp);
	else if (term->search == SEARCH_FAILURE)
	{
		ft_dprintf(STDOUT_FILENO, "(failed reverse-i-search)`%s': ", buff_tmp);
		if (term->buffer)
		{
			ft_putstr_fd(term->buffer, STDERR_FILENO);
			replace_cursor(term, *buff_tmp);
		}
	}
}

void		walking_history(const char *buff_tmp, t_read *term, t_lst **history)
{
	while (*history && (*history)->next && *buff_tmp)
	{
		if (ft_strstr((*history)->content, buff_tmp))
		{
			term->search = SEARCH_SUCCESS;
			goto_reverse(term, buff_tmp);
			ft_strdel(&term->buffer);
			term->buffer = ft_memalloc(BUFF_SIZE + 1);
			insert_str_in_buffer((*history)->content, term);
			*history = (*history)->next;
			replace_cursor(term, *buff_tmp);
			return ;
		}
		*history = (*history)->next;
	}
	term->search = SEARCH_FAILURE;
	goto_reverse(term, buff_tmp);
}
