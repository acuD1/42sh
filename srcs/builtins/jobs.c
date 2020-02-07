/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 01:20:11 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	print_longjob(t_job *job)
{
	t_process	*process;
	t_lst		*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		process = ((t_process *)ptr->content);
		if (ptr == job->process_list)
			printf("[%d]%c %d %-24s %s\n", job->jobc_id, job->jobc_last
			, process->pid, signal_msg(process->status), "process->cmd");
		else
			printf("     %d %24s%s\n", process->pid
			, signal_msg(process->status), "process->command");
		ptr = ptr->next;
	}
}

static void	print_job(t_job *job, uint64_t opt, char *name)
{
	if (!job)
	{
		dprintf(STDERR_FILENO, "42sh: jobs: %s: no such job\n", name);
		return ;
	}
	if (opt & (1ULL << 15))
		printf("%d\n", job->pgid);
	else if (opt & (1ULL << 11))
		print_longjob(job);
	else
		printf("[%d]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
		, (job_is_stopped(job)) ? "Stopped" : "Done", job->command);
}

int8_t		builtin_jobs(t_core *shell, t_process *process)
{
	uint64_t	opt;
	t_lst		*job_list;
	t_job		*job;
	int			argc;
	int			i;

	argc = ft_tablen(process->av);
	job_list = shell->launched_jobs;
	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (shell->launched_jobs)
		update_status(shell);
	if ((opt = ft_get_options(argc, process->av, "lp")) & (1ULL << 63))
		print_usage("42sh: jobs", opt & 0xFF, "jobs [-lp] [jobspec ...]");
	if (i == argc)
		while (job_list)
		{
			print_job(job_list->content, opt, NULL);
			job_list = job_list->next;
		}
	while (i < argc)
	{
		job = get_job(shell->launched_jobs, process->av[i]);
		print_job(job, opt, process->av[i++]);
	}
	return (SUCCESS);
}
