/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:44:14 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/18 19:24:22 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

static void		del_job(t_lst **job)
{
	free_process_list(&(((t_job*)(*job)->content)->process_list));
	free((*job)->content);
	(*job)->content = NULL;
	free(*job);
	*job = NULL;
}

static void		init_launcher_fc
	(t_core *shell, t_job *job, t_process *process, char **argv)
{
	ft_bzero(process, sizeof(t_process));
	ft_bzero(job, sizeof(t_job));
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
	t_lst		*ptr;
	t_job		job;

	job_ptr = NULL;
	ptr = shell->job_list;
	init_launcher_fc(shell, &job, &process, argv);
	ft_lstappend(&(job.process_list), ft_lstnew(&process, sizeof(t_process)));
	if (ft_lstappend(&job_ptr, ft_lstnew(&job, sizeof(t_job))) == NULL)
	{
		free_process_list(&(job.process_list));
		return (FAILURE);
	}
	job_ptr->next = ptr;
	shell->job_list = job_ptr;
	exec_process(shell, job_ptr->content, job.process_list->content);
	shell->job_list = ptr;
	job_ptr->next = NULL;
	if (job_is_completed(job_ptr->content))
		del_job(&job_ptr);
	else
		ft_lstappend(&(shell->launched_jobs), job_ptr);
	return (shell->status == 127 ? FAILURE : SUCCESS);
}
