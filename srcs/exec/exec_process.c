/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/13 23:10:26 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

/*
**	exec_process takes for parameter t_lst *env for now because we can set
**	a temporary environnement if we use the env builtin.
*/

static int8_t	job_part_completed(t_job *job, t_process *process)
{
	t_lst *ptr;

	ptr = job->process_list;
	while (ptr != NULL && ptr->content != process)
	{
		if (((t_process *)ptr->content)->completed != TRUE)
			return (FALSE);
		ptr = ptr->next;
	}
	return (TRUE);
}

static void		control_process
	(t_core *shell, t_job *job, t_process *process, int *fds)
{
	if (process->pgid == -1)
		job->pgid = process->pid;
	process->pgid = job->pgid;
	if ((process->stopped != TRUE || !cond(job->process_list))
		&& fds[1] == STDOUT_FILENO
		&& setpgid(process->pid, process->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: setpgid error\n");
	if (process->stopped != TRUE && fds[1] == STDOUT_FILENO)
	{
		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
		wait_for_process(shell, shell->job_list, process);
		if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
	}
	else if (fds[1] == STDOUT_FILENO && cond(job->process_list))
		wait_for_process(shell, shell->job_list, process);
	else
		process->stopped = FALSE;
}

static void		check_filepath(t_core *shell, t_process *process)
{
	int			ret;

	if (process->bin == NULL)
	{
		dprintf(STDERR_FILENO, "42sh: %s: command not found\n", process->av[0]);
		process->status = 127;
	}
	else if ((ret = ft_access(process->bin, F_OK | X_OK)) != SUCCESS)
	{
		ft_perror(process->av[0], NULL, ret);
		process->status = 126;
	}
	else if (is_dir(process->bin))
	{
		ft_perror(process->av[0], NULL, EISDIR);
		process->status = 126;
	}
	else
		return ;
	shell->status = process->status;
	process->completed = TRUE;
}

void			exec_process
	(t_core *shell, t_job *job, t_process *process, int *fds)
{
	if (job_part_completed(job, process))
		job->pgid = -1;
	process->pgid = job->pgid;
	if (process->completed)
		return ;
	if (process->av)
		get_bin(shell, process);
	check_filepath(shell, process);
	if (process->completed)
		return ;
	else if (process->bin != NULL)
	{
		if ((process->pid = fork()) == 0)
			launch_process(shell, process, fds[0], fds[1]);
		else if (process->pid < 0)
			print_and_quit(shell, "42sh: fork failure\n");
		if (shell->mode & I_MODE)
			control_process(shell, job, process, fds);
	}
}
