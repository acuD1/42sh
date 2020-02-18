/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/18 00:03:37 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	can_bg_run(t_core *shell, char **argv)
{
	int	argc;

	argc = ft_tablen(argv);
	if (!(shell->is_interactive))
		dprintf(STDERR_FILENO, "42sh: bg: no job control\n");
	else if ((argc == 1 || (argc == 2 && ft_strcmp(argv[1], "--") == 0))
		&& get_job(shell->launched_jobs, NULL) == NULL)
		dprintf(STDERR_FILENO, "42sh: bg: current: no such job\n");
	else
		return (SUCCESS);
	return (FAILURE);
}

int8_t		builtin_bg(t_core *shell, t_process *process)
{
	t_job	*job;
	int		i;

	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (can_bg_run(shell, process->av) != SUCCESS)
		return (1);
	if (process->av[i] && process->av[i][0] == '-' && process->av[i][1] != 0)
		dprintf(STDERR_FILENO
		, "42sh: bg: -%c: invalid option\nfb: usage: fb [jobspec]\n"
		, process->av[i][1]);
	while (process->av[i])
	{
		job = get_job(shell->launched_jobs, process->av[i]);
		if (!job)
		{
			dprintf(STDERR_FILENO, "42sh: bg: %s: no such job\n"
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
