/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/12 15:58:24 by mpivet-p         ###   ########.fr       */
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
			ft_printf("[%d]%c %d %-24s %s\n", job->jobc_id, job->jobc_last
			, process->pid, signal_msg(process->status), process->command);
		else
			ft_printf("     %d %24s%s\n", process->pid
			, signal_msg(process->status), process->command);
		ptr = ptr->next;
	}
}

static void	print_job(t_job *job, u_int64_t opt, const char *name)
{
	if (!job)
	{
		ft_dprintf(STDERR_FILENO, "42sh: jobs: %s: no such job\n", name);
		return ;
	}
	if (opt & (1ULL << 15))
		ft_printf("%d\n", job->pgid);
	else if (opt & (1ULL << 11))
		print_longjob(job);
	else
		ft_printf("[%d]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
		, (job_is_stopped(job)) ? "Stopped" : "Done", job->command);
}

int8_t		builtin_jobs(t_core *shell, t_process *process)
{
	u_int64_t	opt;
	t_lst		*job_list;
	t_job		*job;
	int			argc;
	int			i;

	argc = ft_tablen(process->av);
	job_list = shell->launched_jobs;
	i = skip_opt(process->av) + 1;
	if (shell->launched_jobs)
		update_status(shell);
	if ((opt = ft_get_options(argc, process->av, "lp")) & (1ULL << 63))
		print_usage("42sh: jobs", opt & 0xFF, "jobs [-lp] [jobspec ...]");
	if (i >= argc)
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
