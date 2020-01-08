/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/08 22:39:55 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static t_job	*get_last_job(t_lst *jobs)
{
	t_job	*ptr;

	while (jobs)
	{
		ptr = jobs->content;
		if (jobs->next != NULL && jobs->next->next == NULL)
			return (ptr);
		jobs = jobs->next;
	}
	return (NULL);
}

static t_job	*get_job_by_id(t_lst *jobs, int id)
{
	t_job	*ptr;

	while (jobs)
	{
		ptr = jobs->content;
		if (ptr->id == id)
			return (ptr);
		jobs = jobs->next;
	}
	return (NULL);
}

static t_job	*get_job_by_name(t_lst *jobs, char *str)
{
	t_job	*ptr;
	int		i;

	while (jobs)
	{
		ptr = jobs->content;
		i = 0;
		while (str[i] == ptr->command[i])
		{
			if (str[i] == 0)
				return (ptr);
			i++;
		}
		jobs = jobs->next;
	}
	return (NULL);
}

int8_t	builtin_fg(t_core *shell, t_process *process)
{
	t_job	*job;
	int		argc;
	int		i;

	i = 1;
	argc = ft_tablen(process->av);
	if (process->av[1] && process->av[1][0] == '%')
		job = get_job_by_id(shell->launched_jobs, ft_atoi(process->av[1] + 1));
	else if (process->av[1])
		job = get_job_by_name(shell->launched_jobs, process->av[1]);
	else
		job = get_last_job(shell->launched_jobs);
	if (!job)
	{
		dprintf(STDERR_FILENO, "42sh: fg: %s: no such job\n", (process->av[1]) ? process->av[1] : "current");
		return (1);
	}
	continue_job(shell, job, TRUE);
	return (SUCCESS);
}
