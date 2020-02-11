/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/10 03:50:59 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	setup_pipes
	(t_core *shell, t_process *process, int *mypipe, int *outfile)
{
	*outfile = STDOUT_FILENO;
	if (process->type == P_PIPE)
	{
		if (pipe(mypipe) < 0)
			print_and_quit(shell, "42sh: pipe failure\n");
		*outfile = mypipe[1];
	}
}

static void	clean_pipes(int *infile, int *outfile, int *mypipe)
{
	if (*infile != STDIN_FILENO)
		close(*infile);
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*infile = mypipe[0];
	mypipe[0] = STDIN_FILENO;
}

static void	condition_fulfilled(t_lst *process)
{
	t_process	*ptr;
	int			cond;

	ptr = ((t_process*)process->content);
	cond = ptr->type;
	if (cond != P_ANDIF && cond != P_ORIF)
		return ;
	else if (cond == P_ANDIF && ptr->status == 0)
		return ;
	else if (cond == P_ORIF && ptr->status != 0)
		return ;
	while (process && (ptr = ((t_process*)process->content))
			&& (ptr->type == cond || ptr->type == P_PIPE))
	{
		((t_process*)process->next->content)->completed = TRUE;
		((t_process*)process->next->content)->status = 1;
		process = process->next;
	}
}

void		launch_job(t_core *shell, t_job *job, int foreground)
{
	t_process	*ptr;
	t_lst		*process;
	int			mypipe[2];
	int			fds[2];

	fds[0] = STDIN_FILENO;
	mypipe[0] = STDIN_FILENO;
	process = job->process_list;
	while (process && (ptr = ((t_process*)process->content)))
	{
		setup_pipes(shell, ptr, mypipe, &fds[1]);
		ptr->stopped = (foreground == TRUE) ? FALSE : TRUE;
		expansion(shell, ptr);
		if (ptr->completed == FALSE)
		{
			launch_blt(shell, job, ptr, fds);
			if (ptr->completed == FALSE)
				exec_process(shell, job, ptr, fds);
		}
		condition_fulfilled(process);
		clean_pipes(&fds[0], &fds[1], mypipe);
		process = process->next;
	}
}
