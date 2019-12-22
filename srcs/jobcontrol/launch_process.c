/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:55:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/22 16:40:16 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	reset_signals(void)
{
	int	i;

	i = 1;
	while (i <= SIGUSR2)
	{
		signal(i, SIG_DFL)
		i++;
	}
}

int8_t	put_process_in_grp(t_core *shell, t_process *process)
{
	process->pid = getpid();
	if (process->pgid == 0)
		process->pgid = process->pid;
	if (setpgid(process->pid, process->pgid) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
		exit(EXIT_FAILURE);
	}
	if (foreground)
	{
		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
		{
			dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
			exit(EXIT_FAILURE);
		}
	}
}

int8_t	launch_process(t_core *shell, t_process *process, int8_t foreground)
{
	//redirections
	if (shell->is_interactive)
	{
		reset_signals();
		put_process_in_grp(shell, process);
	}
	if (infile != STDIN_FILENO)
	{
		dup2 (infile, STDIN_FILENO);
		close (infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2 (outfile, STDOUT_FILENO);
		close (outfile);
	}
}

int8_t	launch_job(t_core *shell, t_lst *job, int8_t foreground)
{
	t_lst	*process;
	int		mypipe[2];
	int		infile;
	int		outfile;

	infile = STDIN_FILENO;
	process = ((t_job*)job->content)->process_list;
	while (process)
	{
		/* Set up pipes, if necessary.	*/
		if (p->next)
		{
			if (pipe(mypipe) < 0)
			{
				perror("pipe");
				exit(1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;

		/* Fork the child processes.	*/
		if ((pid = fork()) == 0)/* This is the child process.	*/
		{
			launch_process(shell, ((t_process*)process->content), foreground);
		}
		else if (pid < 0) /* The fork failed.	*/
		{
			perror("fork");
			exit(1);
		}
		else /* This is the parent process.	*/
		{
			((t_process*)process->content)->pid = pid;
			if (shell->is_interactive)
			{
				if (((t_job)job->content)->pgid <= 0)
					((t_job)job->cotnent)->pgid = pid;
				if (setpgid(pid, j->pgid) != SUCCESS)
				{
					dprintf("42sh: setpgid error\n");
					quit_shell(shell, EXIT_FAILURE, FALSE);
				}
			}
		}
		/* Clean up after pipes.	*/
		if (infile != STDIN_FILENO)
			close(infile);
		if (outfile != STDOUT_FILENO)
			close(outfile);
		infile = mypipe[0];
		process = process->next;
	}

	if (!shell->is_interactive)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(shell, job, FALSE);
	else
		put_job_in_background(shell, job, FALSE);
}
