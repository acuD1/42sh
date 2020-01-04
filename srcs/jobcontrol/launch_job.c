/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:14:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/04 18:36:26 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	setup_pipes(t_core *shell, t_process *process, int *mypipe, int *outfile)
{
	*outfile = STDOUT_FILENO;
	if (process->type == P_PIPE) /* Setup pipes */
	{
		if (pipe(mypipe) < 0)
			print_and_quit(shell, "42sh: pipe failure\n");
		*outfile = mypipe[1];
	}
}

static void	clean_pipes(int *infile, int *outfile, int *mypipe)
{
		if (*infile != STDIN_FILENO)/* Clean up after pipes.	*/
			close(*infile);
		if (*outfile != STDOUT_FILENO)
			close(*outfile);
		*infile = mypipe[0];
		mypipe[0] = STDIN_FILENO;
}

static void	place_job(t_core *shell, t_job *job, int8_t foreground)
{
	if (!shell->is_interactive)
		wait_for_job(shell, job);
	else if (foreground == TRUE)
		put_job_in_foreground(shell, job, FALSE);
	else
		put_job_in_background(shell, job, FALSE);
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
	foreground = (job->type == P_AND) ? FALSE : TRUE;
	while (process)
	{
		ptr = ((t_process*)process->content);
		setup_pipes(shell, ptr, mypipe, &outfile);

		if ((ptr->pid = fork()) == 0)/* CHILD PROCESS */
			launch_process(shell, ptr, infile, outfile);
		else if (ptr->pid < 0) /* FORK ERROR */
			print_and_quit(shell, "42sh: fork failure\n");
		/* PARENT PROCESS */
		if (shell->is_interactive)
		{
			job->pgid = (ptr->pgid <= 0) ? ptr->pid : job->pgid;
			if (setpgid(ptr->pid, job->pgid) != SUCCESS)
				print_and_quit(shell, "42sh: setpgid error\n");
		}
		clean_pipes(&infile, &outfile, mypipe);

		process = process->next;
	}
//	place_job(shell, job, foreground);
}
