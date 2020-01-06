/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:36:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/06 21:38:18 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			wait_for_job(t_core *shell, t_job *job)
{
	pid_t	pid;
	int		status;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(shell, pid, status) && !job_is_stopped(job) && !job_is_completed(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void	wait_for_process(t_core *shell, t_process *process)
{
	pid_t	pid;
	int		status;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(shell, pid, status) && process->completed == FALSE && process->stopped == FALSE)
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}
