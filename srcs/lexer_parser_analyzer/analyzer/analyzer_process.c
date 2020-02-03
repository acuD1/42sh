/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:30 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 18:02:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_process(t_process *new)
{
	ft_bzero(new, sizeof(t_process));
	new->command = NULL;
	new->type = P_START;
}

/*
t_process		*fetch_process(t_process *process)
{
	t_process	*new;

	new = NULL;
	new = process;
	if (!process)
		return (NULL);
	if (process->av)
		new->av = process->av;
	else
		new->av = NULL;
	if (process->type)
		new->type = process->type;
	else
		new->type = P_START;
	if (process->assign_list)
		new->assign_list = process->assign_list;
	else
		new->assign_list = NULL;
	if (process->redir_list)
		new->redir_list = process->redir_list;
	else
		new->redir_list = NULL;
	return (new);
}
*/

t_analyzer	*process_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	anal->process.redir_list = anal->redir_list;
	ft_lstappend(&anal->process_list,
		ft_lstnew(&anal->process, sizeof(t_process)));
	anal->redir_list = NULL;
	init_process(&anal->process);
	anal->state = A_SEPARATOR;
	return (anal);
}
