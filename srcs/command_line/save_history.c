/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:33 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/09 16:26:10 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sh42.h"

/*
**	Save the last line inserted in history list
**	Next ptr to the last line saved
*/

void			save_history(t_read *term)
{
	t_lst		*saved;

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
}
