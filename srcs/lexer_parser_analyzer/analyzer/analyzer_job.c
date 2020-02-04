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
	new->command = NULL;
	new->type = P_END;
	new->process_list = NULL;
}

t_analyzer	*job_analyze(t_analyzer *anal, t_core *shell)
{
	anal = process_analyze(anal, shell);
	anal->job.process_list = anal->process_list;
	ft_lstappend(&anal->job_list,
		ft_lstnew(&anal->job, sizeof(t_job)));
	anal->process_list = NULL;
	init_job(&anal->job);
	anal->state = A_START;
	return (anal);
}
