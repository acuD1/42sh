/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/10 11:27:33 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			goto_reverse(t_read *input, char *buff_tmp, int8_t mode)
{
	goto_prompt(input);
	xtputs(input->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(input->tcaps[CLR_LINES], 1, my_outc);
	if (mode == SUCCESS)
		ft_dprintf(STDIN_FILENO, "(reverse-i-search)`%s': ", buff_tmp);
	else if (mode == FAILURE)
		ft_dprintf(STDIN_FILENO, "(failed reverse-i-search)`%s': ", buff_tmp);
}

void			walking_history(char *buff_tmp, t_read *input, t_lst **history)
{
	while ((*history)->next)
	{
		if (ft_strstr((*history)->content, buff_tmp))
		{
			goto_reverse(input, buff_tmp, SUCCESS);
			ft_bzero(input->buffer, ft_strlen(input->buffer));
			input->x = ft_strlen(buff_tmp) + 23;
			insert_str_in_buffer((*history)->content, input);
			if ((*history)->next)
				(*history) = (*history)->next;
			return ;
		}
		(*history) = (*history)->next;
	}
	goto_reverse(input, buff_tmp, FAILURE);
}

int8_t			insert_in_search(t_read *input, int64_t *i, char buff[])
{
	uint64_t	value;

	value = get_mask(buff);
	if (is_print(*buff))
	{
		input->tmp_buff[++(*i)] = *buff;
		goto_reverse(input, input->tmp_buff, SUCCESS);
	}
	else if (value == BS_KEY)
	{
		input->tmp_buff[*i] = 0;
		if (*i <= -1)
			return (SUCCESS);
		(*i)--;
	}
	else if (value != CTRL_R)
		return (FAILURE);
	return (SUCCESS);
}

void			search_in_history(t_read *input)
{
	char		buff[READ_SIZE + 1];
	int64_t		i;
	t_lst		*history;

	i = -1;
	input->tmp_buff = ft_memalloc(BUFF_SIZE);
	ft_bzero(buff, READ_SIZE + 1);
	history = input->history;
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (insert_in_search(input, &i, buff) == FAILURE)
		{
			ft_strdel(&input->tmp_buff);
			return ;
		}
		walking_history(input->tmp_buff, input, &history);
	}
}

void			research_mode(t_read *input)
{
	char		*saved;

	saved = NULL;
	if (input->tmp_buff)
	{
		saved = ft_strdup(input->tmp_buff);
		ft_strdel(&input->tmp_buff);
	}
	goto_reverse(input, "", SUCCESS);
	search_in_history(input);
	if (saved)
	{
		input->tmp_buff = ft_strdup(saved);
		ft_strdel(&saved);
	}
	goto_prompt(input);
	ft_dprintf(STDIN_FILENO, "%s", input->buffer);
	input->x += ft_strlen(input->buffer);
	input->width = input->x;
	input->x_index = input->x;
	input->y = input->width / input->ws_col;
}
