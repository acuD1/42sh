/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static int8_t	launch_bg_job(t_core *shell, char *job_name)
{
	t_job	*job;

	job = get_job(shell->launched_jobs, job_name);
	if (!job)
	{
		ft_dprintf(STDERR_FILENO, "42sh: bg: %s: no such job\n"
		, (job_name) ? job_name : "current");
		return (1);
	}
	job->notified = FALSE;
	continue_job(shell, job, FALSE);
	ft_dprintf(STDERR_FILENO, "[%d] %s &\n", job->jobc_id, job->command);
	return (0);
}

int8_t			builtin_bg(t_core *shell, t_process *process)
{
	size_t	i;

	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (!(shell->is_interactive))
	{
		ft_dprintf(STDERR_FILENO, "42sh: bg: no job control\n");
		return (1);
	}
	if (process->av[i] && process->av[i][0] == '-' && process->av[i][1] != 0)
		ft_dprintf(STDERR_FILENO
		, "42sh: bg: -%c: invalid option\nbg: usage: bg [jobspec]\n"
		, process->av[i][1]);
	if (i == ft_tablen(process->av))
		return (launch_bg_job(shell, NULL));
	while (process->av[i])
	{
		if (launch_bg_job(shell, process->av[i]) != 0)
			return (1);
		i++;
	}
	return (SUCCESS);
}
