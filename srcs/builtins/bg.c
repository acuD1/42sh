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

static int8_t	can_bg_run(t_core *shell, char **argv)
{
	size_t	argc;

	argc = ft_tablen(argv);
	if (!(shell->is_interactive))
		ft_dprintf(STDERR_FILENO, "42sh: bg: no job control\n");
	else if ((argc == 1 || (argc == 2 && ft_strcmp(argv[1], "--") == 0))
		&& get_job(shell->launched_jobs, NULL) == NULL)
		ft_dprintf(STDERR_FILENO, "42sh: bg: current: no such job\n");
	else
		return (SUCCESS);
	return (FAILURE);
}

int8_t			builtin_bg(t_core *shell, t_process *process)
{
	t_job	*job;
	size_t	i;

	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (can_bg_run(shell, process->av) != SUCCESS)
		return (1);
	if (process->av[i] && process->av[i][0] == '-' && process->av[i][1] != 0)
		ft_dprintf(STDERR_FILENO
		, "42sh: bg: -%c: invalid option\nfb: usage: fb [jobspec]\n"
		, process->av[i][1]);
	while (process->av[i])
	{
		job = get_job(shell->launched_jobs, process->av[i]);
		if (!job)
		{
			ft_dprintf(STDERR_FILENO, "42sh: bg: %s: no such job\n"
			, (process->av[i]) ? process->av[1] : "current");
			return (1);
		}
		job->notified = FALSE;
		continue_job(shell, job, FALSE);
		format_job_info(job);
		i++;
	}
	return (SUCCESS);
}
