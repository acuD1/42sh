/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:58:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/21 22:00:04 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/* int8_t 		dbug(const char *path, t_read *in) */
/* { */
/*     int 	fd; */
/* 	int		i = -1; */
/*  */
/*     if ((fd = open(path, O_WRONLY)) < 0) */
/*         return (-1); */
/*     dprintf(fd,"FLAG[%d] tab[%d]\n\n tmp_buff=[%s]\n buffer[%s]\n", in->found, ft_tablen(in->cmd), in->tmp_buff, in->buffer); */
/* 	while (in->cmd[++i]) */
/*     	dprintf(fd,"i=[%d] >> cmd=[%s]\n", i, in->cmd[i]); */
/*     return (1); */
/* } */

uint8_t		check_eof(t_read *term)
{
	int		i;

	i = -1;
	while (term->tmp_buff[i++] && term->tmp_buff[i] != NEW_LINE)
		;
	if (!ft_strcmp(term->buffer, term->cmd[term->found]))
	{
		term->found++;
		if (term->found < ft_tablen(term->cmd))
			return (FALSE);
		term->found = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

int8_t		check_hc_reader(t_read *term)
{
	if (read_multiline(term, FALSE) == FALSE)
	{
		term->sub_prompt = FALSE;
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
	while (TRUE)
	{
		ft_strdel(&term->buffer);
		term->buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(term, PS3);
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
	term->heredoc = ft_strsplit(term->buffer, "\n");
}
