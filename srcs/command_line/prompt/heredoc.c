/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:58:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/24 11:51:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		heredoc_error(t_read *term, char *key)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: warning: here-document delimited by end-of-file (wanted `%s')\n", key);
	term->sub_prompt++;
	if (term->sub_prompt == ft_tablen(term->cmd))
		return (FALSE);
	return (TRUE);
}

uint8_t		check_eof(t_read *term)
{
	int		i;

	i = -1;
	while (term->tmp_buff[i++] && term->tmp_buff[i] != NEW_LINE)
		;
	if (!ft_strcmp(term->buffer, term->cmd[term->sub_prompt]))
	{
		term->sub_prompt++;
		if (term->sub_prompt < ft_tablen(term->cmd))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

int8_t		check_hc_reader(t_read *term)
{
	if (read_multiline(term, FALSE) == FALSE)
	{
		if (term->flag == TRUE)
			return (heredoc_error(term, term->cmd[term->sub_prompt]));
		if (check_eof(term) == FALSE)
		{
			term->buffer = ft_strjoinf(term->tmp_buff, term->buffer, 2);
			term->buffer = ft_strjoinf(term->buffer, "\n", 1);
			ft_strdel(&term->tmp_buff);
			term->tmp_buff = ft_strdup(term->buffer);
			return (TRUE);
		}
	}
	return (FALSE);
}

void		load_heredoc(t_read *term)
{
	term->buffer = ft_strjoinf(term->buffer, "\n", 1);
	term->tmp_buff = ft_strdup(term->buffer);
	term->status = CMD_SUBPROMPT;
	ft_printtab(term->cmd);
	while (TRUE)
	{
		ft_strdel(&term->buffer);
		term->buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(term, PS2);
		if (check_hc_reader(term) == TRUE)
			continue ;
		else
			break ;
		if (term->status == CMD_PROMPT)
			return ;
	}
	term->tmp_buff = ft_strjoinf(term->tmp_buff, term->buffer, 1);
	ft_strdel(&term->buffer);
	term->buffer = ft_strdup(term->tmp_buff);
	ft_strdel(&term->tmp_buff);
	term->status = CMD_DONE;
	ft_tabfree(term->cmd);
}
