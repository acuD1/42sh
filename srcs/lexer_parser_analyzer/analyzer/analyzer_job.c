/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:53:51 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:01 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_job(t_job *new)
{
	new->command = ft_strnew(0);
	new->type = P_END;
	new->process_list = NULL;
}

// t_job		*fetch_job(t_job *job)
// {
// 	t_job	*new;

// 	if (!job)
// 		return (NULL);
// 	new = job;
// 	new->type = job->type;
// 	if (job->command)
// 		new->command = job->command;
// 	else
// 		new->command = NULL;
// 	if (job->process_list)
// 		new->process_list = job->process_list;
// 	else
// 		new->process_list = NULL;
// 	return (new);
// }

t_analyzer	*job_analyze(t_analyzer *anal, t_core *shell)
{
	anal = process_analyze(anal, shell);
	anal->job.process_list = anal->process_list;
	ft_lstappend(&anal->job_list,
		ft_lstnew(&anal->job, sizeof(t_job)));
	anal->process_list = NULL;
	init_job(&anal->job);
	if (anal->lexer->next
		&& !ft_strcmp("(null)", ((t_token*)anal->lexer->next->content)->data))
		anal->state = A_STOP;
	else
		anal->state = A_START;
	return (anal);
}
