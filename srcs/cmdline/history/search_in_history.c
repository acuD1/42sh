/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/07 01:24:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		goto_reverse(t_read *term, char *buff_tmp, int8_t mode)
{
	goto_prompt(term);
	xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
	if (mode == SUCCESS)
		ft_dprintf(STDIN_FILENO, "(reverse-i-search)`%s': ", buff_tmp);
	else if (mode == FAILURE)
		ft_dprintf(STDIN_FILENO, "(failed reverse-i-search)`%s': ", buff_tmp);
}

static void		walking_history(char *buff_tmp, t_read *term, t_lst **history)
{
	while ((*history)->next && *buff_tmp)
	{
		if (ft_strstr((*history)->content, buff_tmp))
		{
			goto_reverse(term, buff_tmp, SUCCESS);
			ft_bzero(term->buffer, ft_strlen(term->buffer));
			term->x = ft_strlen(buff_tmp) + 23;
			insert_str_in_buffer((*history)->content, term);
			if ((*history)->next)
				(*history) = (*history)->next;
			return ;
		}
		(*history) = (*history)->next;
	}
	goto_reverse(term, buff_tmp, FAILURE);
}

static int8_t	insert_in_search(t_read *term, int64_t *i, char buff[])
{
	u_int64_t	value;

	value = get_mask(buff);
	if (ft_is_print(*buff))
	{
		term->tmp_buff[++(*i)] = *buff;
		goto_reverse(term, term->tmp_buff, SUCCESS);
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

static void		search_in_history(t_read *term)
{
	char		buff[READ_SIZE + 1];
	int64_t		i;
	t_lst		*history;

	i = -1;
	term->tmp_buff = ft_memalloc(BUFF_SIZE);
	ft_bzero(buff, READ_SIZE + 1);
	history = term->history;
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (insert_in_search(term, &i, buff) == FAILURE)
		{
			ft_strdel(&term->tmp_buff);
			return ;
		}
		walking_history(term->tmp_buff, term, &history);
	}
}

void			research_mode(t_read *term)
{
	char		*saved;

	saved = NULL;
	if (term->tmp_buff)
	{
		saved = ft_strdup(term->tmp_buff);
		ft_strdel(&term->tmp_buff);
	}
	goto_reverse(term, "", SUCCESS);
	search_in_history(term);
	if (saved)
	{
		term->tmp_buff = ft_strdup(saved);
		ft_strdel(&saved);
	}
	goto_prompt(term);
	ft_dprintf(STDIN_FILENO, "%s", term->buffer);
	term->x += ft_strlen(term->buffer);
	term->width = term->x;
	term->x_index = term->x;
	term->y = term->width / term->ws_col;
}
