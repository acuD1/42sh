/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:44:14 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/02 16:40:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		del_job(t_lst *job)
{
	free_process_list(&(((t_job*)job->content)->process_list));
	free(job->content);
	free(job);
}

static void		init_process_fc(t_core *shell, t_process *process, char **argv)
{
	process->av = argv;
	process->envp = set_envp(shell);
	process->pipe[0] = STDIN_FILENO;
	process->pipe[1] = STDOUT_FILENO;
	process->close[0] = -1;
	process->close[1] = -1;
}

int8_t			fc_launch_editor(t_core *shell, char **argv)
{
	t_process	process;
	t_lst		*job_ptr;
	t_job		job;

	job_ptr = NULL;
	ft_bzero(&job, sizeof(t_job));
	ft_bzero(&process, sizeof(t_process));
	init_process_fc(shell, &process, argv);
	ft_lstappend(&(job.process_list), ft_lstnew(&process, sizeof(t_process)));
	if (job.process_list == NULL)
		return (FAILURE);
	if (ft_lstappend(&job_ptr, ft_lstnew(&job, sizeof(t_job))) == NULL)
	{
		free_process_list(&(job.process_list));
		return (FAILURE);
	}
	exec_process(shell, job_ptr->content, job.process_list->content);
	if (job_is_completed(job_ptr->content))
		del_job(job_ptr);
	else
		ft_lstappend(&(shell->launched_jobs), job_ptr);
	return (SUCCESS);
}
