/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:33 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/03 18:55:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sh42.h"

/*
**	Open ".history" file to write history datas at the end of file
*/

void			write_history(char *history_data)
{
	int		fd;

	if (!history_data)
		return ;
	if ((fd = open("./.history", MODE_WRITE, PERMISSIONS)) == -1)
		dprintf(STDIN_FILENO, "can't open history file\n");
	else
	{
		if (write(fd, history_data, ft_strlen(history_data)) == FAILURE
			|| write(fd, "\n", 1) == FAILURE)
		{
			dprintf(2, "can't open history file\n");
			close(fd);
			return ;
		}
	}
	close(fd);
}

/*
**	Save the last line inserted in history list
**	Next ptr to the last line saved
*/

void			save_history(t_read *term)
{
	t_lst		*saved;

	saved = NULL;
	if (ft_strcmp(term->buffer, ""))
	{
		saved = ft_memalloc(sizeof(*saved));
		saved->prev = NULL;
		saved->next = term->history;
		saved->data = ft_strdup(term->buffer);
		if (term->history)
			term->history->prev = saved;
		term->history = saved;
		term->history_index = NULL;
	}
	write_history(saved->data);
}
