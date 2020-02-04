/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:30 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:34 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			init_process(t_process *new)
{
	ft_bzero(new, sizeof(t_process));
	new->command = NULL;
	new->type = P_START;
}

t_analyzer		*process_analyze(t_analyzer *anal, t_core *shell)
{
	anal->process.redir_list = anal->redir_list;
	ft_lstappend(&anal->process_list,
		ft_lstnew(&anal->process, sizeof(t_process)));
	anal->redir_list = NULL;
	init_process(&anal->process);
	anal->state = A_SEPARATOR;
	(void)shell;
	return (anal);
}
