/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/10 21:37:44 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	print_job(t_job *job, uint64_t opt)
{
	static char	*long_status[1] = {"Suspended: 18"};
	static char	*status[1] = {"Stopped"};

	if (opt & (1ULL << 15))
		printf("%d\n", job->pgid);
	else if (opt & (1ULL << 11))
		printf("[%d]%c  %d %s\t\t%s\n", job->jobc_id, job->jobc_last, job->pgid, long_status[0], job->command);
	else
		printf("[%d]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last, status[0], job->command);
}

int8_t	builtin_jobs(t_core *shell, t_process *process)
{
	uint64_t	opt;
	t_lst		*job;
	int			argc;

	(void)shell;
	argc = ft_tablen(process->av);
	job = shell->launched_jobs;
	if ((opt = get_options(argc, process->av, "lp")) & OPT_ERROR)
		print_usage("42sh: jobs", opt & 0xFF, "jobs [-lp] [jobspec ...]");
	while (job)
	{
		print_job(job->content, opt);
		job = job->next;
	}
	return (SUCCESS);
}
