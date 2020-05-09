/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 20:46:16 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <signal.h>

void			goto_reverse(t_read *term, const char *buff_tmp)
{
	ssize_t		str_len;
	ssize_t		i;

	i = -1;
	str_len = (ssize_t)ft_strlen(buff_tmp);
	str_len += (ssize_t)ft_strlen(term->buffer) + (ssize_t)term->search - 1;
	term->y = str_len / term->ws_col;
	while (term->buffer[++i])
		if (term->buffer[i] == '\n')
			term->y++;
	goto_prompt(term);
	xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
	if (term->search == SEARCH_SUCCESS)
		ft_dprintf(STDOUT_FILENO, "(reverse-i-search)`%s': ", buff_tmp);
	else if (term->search == SEARCH_FAILURE)
		ft_dprintf(STDOUT_FILENO, "(failed reverse-i-search)`%s': ", buff_tmp);
}

static void		walking_history
	(const char *buff_tmp, t_read *term, t_lst **history)
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
			return ;
		}
		*history = (*history)->next;
	}
	term->search = SEARCH_FAILURE;
	goto_reverse(term, buff_tmp);
}

static int8_t	insert_in_search(t_read *term, const char buff[], int *i)
{
	u_int64_t	value;

	value = get_mask(buff);
	if (ft_is_print(*buff))
	{
		term->tmp_buff[++(*i)] = *buff;
		if (term->search == SEARCH_FAILURE)
			goto_reverse(term, term->tmp_buff);
		else
			goto_reverse(term, term->tmp_buff);
	}
	else if (value == BS_KEY && *term->tmp_buff)
	{
		term->tmp_buff[*i] = 0;
		if (*i <= -1)
			return (SUCCESS);
		(*i)--;
	}
	else if (value != CTRL_R && value != BS_KEY)
		return (FAILURE);
	return (SUCCESS);
}

static void		research_in_history(t_read *term)
{
	char		buff[READ_SIZE + 1];
	t_lst		*history;
	int			i;

	i = -1;
	term->tmp_buff = ft_memalloc(BUFF_SIZE + 1);
	ft_bzero(buff, READ_SIZE + 1);
	history = term->history;
	goto_reverse(term, "");
	ft_putstr_fd(term->buffer, STDOUT_FILENO);
	sigint_special_handler();
	while (read(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (!term->tmp_buff)
			return ;
		if (insert_in_search(term, buff, &i) == FAILURE)
		{
			ft_strdel(&term->tmp_buff);
			signal(SIGINT, sigint_handler);
			return ;
		}
		history = (*buff == 127) ? term->history : history;
		walking_history(term->tmp_buff, term, &history);
		ft_bzero(buff, READ_SIZE + 1);
	}
}

void			research_mode(t_read *term)
{
	char		*saved;
	char		*tmp;
	ssize_t		i;

	saved = NULL;
	tmp = NULL;
	i = -1;
	term->search = SEARCH_SUCCESS;
	if (term->tmp_buff)
	{
		saved = ft_strdup(term->tmp_buff);
		ft_strdel(&term->tmp_buff);
	}
	research_in_history(term);
	if (saved)
	{
		term->tmp_buff = ft_strdup(saved);
		ft_strdel(&saved);
	}
	goto_prompt(term);
	tmp = ft_strdup(term->buffer);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(tmp, term);
	ft_strdel(&tmp);
}
