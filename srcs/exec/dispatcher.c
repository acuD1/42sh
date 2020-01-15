/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/15 21:38:41 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		setup_pipes(t_core *shell, t_process *process
		, int *mypipe, int *outfile)
{
	*outfile = STDOUT_FILENO;
	if (process->type == P_PIPE)
	{
		if (pipe(mypipe) < 0)
			print_and_quit(shell, "42sh: pipe failure\n");
		*outfile = mypipe[1];
	}
}

static void		clean_pipes(int *infile, int *outfile, int *mypipe)
{
	if (*infile != STDIN_FILENO)
		close(*infile);
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*infile = mypipe[0];
	mypipe[0] = STDIN_FILENO;
}

static void		place_job(t_core *shell, t_job *job, int8_t foreground)
{
	if (!shell->is_interactive)
		wait_for_job(shell, shell->job_list, job);
	else if (foreground == TRUE)
		put_job_in_foreground(shell, shell->job_list, job, FALSE);
	else
	{
		printf("[1] pgid\n");
		put_job_in_background(shell, job, FALSE);
	}
}

static int8_t	condition_fulfilled(t_core *shell, int cond)
{
	if (cond != P_ANDIF && cond != P_ORIF)
		return (SUCCESS);
	else if (cond == P_ANDIF && shell->status == 0)
		return (SUCCESS);
	else if (cond == P_ORIF && shell->status != 0)
		return (SUCCESS);
	return (FAILURE);
}

void			launch_job(t_core *shell, t_job *job)
{
	t_process	*ptr;
	t_lst		*process;
	int8_t		foreground;
	int			cond;
	int			mypipe[2];
	int			infile;
	int			outfile;

	cond = 0;
	infile = STDIN_FILENO;
	process = job->process_list;
	foreground = (job->type == P_AND) ? FALSE : TRUE;
	while (process)
	{
		ptr = ((t_process*)process->content);
		setup_pipes(shell, ptr, mypipe, &outfile);
		ptr->stopped = (foreground == TRUE) ? FALSE : TRUE;
		if (condition_fulfilled(shell, cond) == SUCCESS)
		{
			expansion(shell, ptr);
			add_assign_env(shell, ptr);
			if (infile == STDIN_FILENO && outfile == STDOUT_FILENO && foreground == TRUE)
				launch_blt(shell, ptr);
			if (ptr->completed != TRUE)
				exec_process(job, ptr, infile, outfile);
		}
		else
			return ;
		clean_pipes(&infile, &outfile, mypipe);
		cond = ptr->type;
		process = process->next;
	}
	if (shell->is_interactive && !job_is_completed(job) && !job_is_stopped(job) && process == NULL)
		place_job(shell, job, foreground);
}
