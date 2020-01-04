/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/04 21:34:59 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
 **	exec_process takes for parameter t_lst *env for now because we can set
 **	a temporary environnement if we use the env builtin.
 */

void	exec_process(t_job *job, t_process *process, int infile, int outfile)
{
	t_core	*shell;
	int		status;

	shell = get_core(NULL);
	if ((process->pid = fork()) == 0)/* CHILD PROCESS */
		launch_process(shell, process, infile, outfile);
	else if (process->pid < 0) /* FORK ERROR */
		print_and_quit(shell, "42sh: fork failure\n");
	if (shell->is_interactive)
	{
		if (job->pgid == 0)
			job->pgid = process->pid;
		process->pgid = job->pgid;
		if (setpgid(process->pid, job->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: setpgid error\n");
		if (process->stopped != TRUE && tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
		if (infile == STDIN_FILENO && outfile == STDOUT_FILENO)
			waitpid(process->pid, &status, WUNTRACED | WCONTINUED);
		if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
	}
}

/*
	Si av :
	{
		si blt
	}
*/
