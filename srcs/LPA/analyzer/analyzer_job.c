/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:53:51 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/06 22:44:41 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_job(t_job *new)
{
	ft_bzero(new, sizeof(t_job));
	new->type = P_END;
}

t_analyzer	*job_analyze(t_analyzer *anal, t_core *shell)
{
	anal = process_analyze(anal, shell);
	anal->job.process_list = anal->process_list;
	ft_lstappend(&anal->job_list,
		ft_lstnew(&anal->job, sizeof(t_job)));
	anal->process_list = NULL;
	init_job(&anal->job);
	if (anal->lexer->next
		&& ((t_token*)anal->lexer->next->content)->id == P_END)
		anal->state = A_STOP;
	else
		anal->state = A_START;
	return (anal);
}
