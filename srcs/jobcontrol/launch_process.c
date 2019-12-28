/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:55:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/28 17:43:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	reset_signals(void)
{
	int	i;

	i = 0;
	while (i++ < SIGUSR2)
		signal(i, SIG_DFL);
}

void	put_process_in_grp(t_core *shell, t_process *process)
{
	process->pid = getpid();
	if (process->pgid == 0)
		process->pgid = process->pid;
	if (setpgid(process->pid, process->pgid) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
		exit(EXIT_FAILURE);
	}
	if (process->stopped != TRUE)
	{
		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
		{
			dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
			exit(EXIT_FAILURE);
		}
	}
}

int8_t	launch_process(t_core *shell, t_process *process, int infile, int outfile)
{
	if (shell->is_interactive)
	{
		reset_signals();
		put_process_in_grp(shell, process);
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	//call_bin
	return (SUCCESS);
}

void	launch_job(t_core *shell, t_job *job)
{
	t_process	*ptr;
	t_lst		*process;
	int8_t		foreground;
	int			mypipe[2];
	int			infile;
	int			outfile;

	infile = STDIN_FILENO;
	process = job->process_list;
	foreground = TRUE; // = (job->type == P_AND) ? FALSE : TRUE;
	while (process)
	{
		ptr = ((t_process*)process->content);
		outfile = STDOUT_FILENO;
		mypipe[0] = STDIN_FILENO;

		if (ptr->type == P_PIPE) /* Setup pipes */
		{
			if (pipe(mypipe) < 0)
				print_and_quit(shell, "42sh: pipe failure\n");
			outfile = mypipe[1];
		}

		if ((ptr->pid = fork()) == 0)/* CHILD PROCESS */
			launch_process(shell, ptr, infile, outfile);
		else if (ptr->pid < 0) /* FORK ERROR */
			print_and_quit(shell, "42sh: fork failure\n");
		else /* PARENT PROCESS */
		{
			if (shell->is_interactive)
			{
				if (job->pgid <= 0)
					job->pgid = ptr->pid;
				if (setpgid(ptr->pid, job->pgid) != SUCCESS)
					print_and_quit(shell, "42sh: setpgid error\n");
			}
		}

		if (infile != STDIN_FILENO)/* Clean up after pipes.	*/
			close(infile);
		if (outfile != STDOUT_FILENO)
			close(outfile);
		infile = mypipe[0];

		process = process->next;
	}
	if (!shell->is_interactive)
		wait_for_job(shell, job);
	else if (foreground != TRUE)
		put_job_in_foreground(shell, job, FALSE);
	else
		put_job_in_background(shell, job, FALSE);
}
