/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:30 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/11 21:39:33 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

void		init_process(t_process *new)
{
	ft_bzero(new, sizeof(t_process));
	new->type = P_START;
	new->pipe[0] = STDIN_FILENO;
	new->pipe[1] = STDOUT_FILENO;
	new->close[0] = -1;
	new->close[1] = -1;
}

t_analyzer	*process_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	anal->process.redir_list = anal->redir_list;
	ft_lstappend(&anal->process_list,
		ft_lstnew(&anal->process, sizeof(t_process)));
	anal->redir_list = NULL;
	init_process(&anal->process);
	anal->state = A_SEPARATOR;
	(void)shell;
	return (anal);
}
