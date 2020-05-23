/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 14:26:30 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

int8_t	builtin_fg(t_core *shell, t_process *process)
{
	t_job	*job;
	int		i;

	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (!(shell->is_interactive))
	{
		ft_dprintf(STDERR_FILENO, "42sh: fg: no job control\n");
		return (1);
	}
	if (process->av[i] && process->av[i][0] == '-' && process->av[i][1] != 0)
		ft_dprintf(STDERR_FILENO
		, "42sh: fg: -%c: invalid option\nfg: usage: fg [jobspec]\n"
		, process->av[i][1]);
	job = get_job(shell->launched_jobs, process->av[i]);
	if (!job)
	{
		ft_dprintf(STDERR_FILENO, "42sh: fg: %s: no such job\n"
		, (process->av[i]) ? process->av[i] : "current");
		return (1);
	}
	ft_printf("%s\n", job->command);
	job->notified = FALSE;
	continue_job(shell, job, TRUE);
	do_job_notification(shell, shell->launched_jobs, FALSE);
	return (SUCCESS);
}
