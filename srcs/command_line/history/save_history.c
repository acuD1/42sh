/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:33 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 15:21:57 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sh42.h"

/*
**	Open "./.42sh_history" file to write history datas at the end of file
*/

int8_t			write_history(t_read *line)
{
	int		fd;
	int		i;
	t_lst	*hst;

	if (!(hst = line->history))
		return ;
	i = 0;
	if ((fd = open(HISTORY_FILE, MODE_WRITE, S_USR_RW | S_GRP_OTH_R)) == -1)
		ft_dprintf(STDIN_FILENO, "can't open history file\n");
	while (hst->next && ++i < HIST_SIZE)
		hst = hst->next;
	while (hst)
	{
		if (write(fd, hst->content, ft_strlen(hst->content)) == FAILURE
			|| write(fd, "\n", 1) == FAILURE)
		{
			ft_dprintf(2, "write failure\n");
			close(fd);
			return (FAILURE);
		}
		hst = hst->prev;
	}
	close(fd);
	return (SUCCESS);
}

/*
**	Save the last line inserted in history list
**	Next ptr to the last line saved
*/

void			save_history(t_read *term)
{
	t_lst		*saved;

	saved = NULL;
	if ((*term).buffer && ft_strlen(term->buffer) > 0)
	{
		saved = ft_memalloc(sizeof(*saved));
		saved->prev = NULL;
		saved->next = term->history;
		saved->content = ft_strdup(term->buffer);
		if (term->history)
			term->history->prev = saved;
		term->history = saved;
		term->history_index = NULL;
		if (term->history->next)
			term->history->content_size = term->history->next->content_size + 1;
	}
}

/*
**	Init history list -> load datas from history file
*/

int8_t			init_history(t_read *term)
{
	char		*line;
	int			fd;
	int			i;
	int			j;

	j = 0;
	i = -1;
	line = NULL;
	if ((fd = open(HISTORY_FILE, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH)) == -1)
		return (FAILURE);
	while (ft_getnextline(fd, &line) > 0)
	{
		term->buffer = ft_memalloc(BUFF_SIZE);
		while (++i < (int)ft_strlen(line))
			term->buffer[i] = line[i];
		save_history(term);
		term->history->content_size = ++j;
		free(line);
		free(term->buffer);
		i = -1;
	}
	free(line);
	close(fd);
	return (SUCCESS);
}
