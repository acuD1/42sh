/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/16 21:58:29 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	builtin_fg(t_core *shell, t_process *process)
{
	t_job	*job;
	int		i;

	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (!(shell->mode & I_MODE))
	{
		dprintf(STDERR_FILENO, "42sh: fg: no job control\n");
		return (1);
	}
	if (process->av[i] && process->av[i][0] == '-' && process->av[i][1] != 0)
		dprintf(STDERR_FILENO
		, "42sh: fg: -%c: invalid option\nfg: usage: fg [jobspec]\n"
		, process->av[i][1]);
	job = get_job(shell->launched_jobs, process->av[i]);
	if (!job)
	{
		dprintf(STDERR_FILENO, "42sh: fg: %s: no such job\n"
		, (process->av[i]) ? process->av[i] : "current");
		return (1);
	}
	printf("%s\n", job->command);
	continue_job(shell, job, TRUE);
	return (SUCCESS);
}
