/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:53:51 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 18:02:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

// ??

void	init_job(t_job *new)
{
	ft_bzero(new, sizeof(t_job));
	new->type = P_END;
}

/*
t_job		*fetch_job(t_job *job)
{
	t_job	*new;

	if (!job)
		return (NULL);
	new = job;
	new->type = job->type;
	if (job->command)
		new->command = job->command;
	else
		new->command = NULL;
	if (job->process_list)
		new->process_list = job->process_list;
	else
		new->process_list = NULL;
	return (new);
}
*/

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
