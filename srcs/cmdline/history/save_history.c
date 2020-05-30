/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:33 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/24 16:41:33 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
**	Open ".42sh_history" file to write history datas at the end of file
*/

static int8_t	history_writer(t_lst *hst, int fd)
{
	ssize_t	i;

	i = 0;
	while (hst->next && ++i < get_history_value("HISTFILESIZE"))
		hst = hst->next;
	while (hst)
	{
		if (write(fd, hst->content, ft_strlen(hst->content)) == FAILURE
			|| write(fd, NEW_LINE, 1) == FAILURE)
		{
			ft_dprintf(STDERR_FILENO, "42sh: write failure in history file\n");
			close(fd);
			return (FAILURE);
		}
		hst = hst->prev;
	}
	close(fd);
	return (SUCCESS);
}

int8_t			write_history(t_core *shell)
{
	char	*history_file;
	int		fd;

	history_file = get_home_value(shell);
	if (!shell->term.history)
	{
		ft_strdel(&history_file);
		return (FAILURE);
	}
	if ((fd = open(history_file, (O_CREAT | O_WRONLY | O_TRUNC)
				, (S_IRUSR | S_IWUSR) | (S_IRGRP | S_IROTH))) == -1)
	{
		ft_strdel(&history_file);
		ft_dprintf(STDERR_FILENO, "42sh: can't open history file\n");
		return (FAILURE);
	}
	ft_strdel(&history_file);
	return (history_writer(shell->term.history, fd));
}

/*
**	Save the last line inserted in history list
**	Next ptr to the last line saved
*/

void			save_history(t_read *term)
{
	t_lst		*saved;

	saved = NULL;
	if (term->buffer && *term->buffer)
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

static void		read_history_file(t_core *shell, int fd)
{
	char		*line;
	size_t		i;

	i = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] && ft_str_isprint(line))
		{
			shell->term.buffer = ft_strdup(line);
			save_history(&shell->term);
			shell->term.history->content_size = ++i;
			ft_strdel(&(shell->term.buffer));
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
}

/*
**	Init history list -> load datas from history file
*/

int8_t			init_history(t_core *shell)
{
	char	*line;
	char	*history_file;
	int		fd;

	line = NULL;
	history_file = get_home_value(shell);
	if ((fd = open(history_file, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_strdel(&history_file);
		return (FAILURE);
	}
	ft_strdel(&history_file);
	read_history_file(shell, fd);
	return (SUCCESS);
}
