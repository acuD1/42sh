/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static void		print_longjob(t_job *job)
{
	static char	running[] = "Running\n";
	t_process	*process;
	char		*msg;
	t_lst		*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		process = ((t_process *)ptr->content);
		msg = job_is_stopped(job) ? signal_msg(process->status) : running;
		if (ptr == job->process_list)
			ft_printf("[%d]%c %d %-23.*s %s\n", job->jobc_id, job->jobc_last
			, process->pid
			, ft_strlen(msg) - 1
			, msg, process->command);
		else
			ft_printf("     %d %-24.*s%s\n", process->pid
			, ft_strlen(msg) - 1
			, msg, process->command);
		ptr = ptr->next;
	}
}

static void		print_job(t_job *job, u_int64_t opt, const char *name)
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
	else if (!job_is_stopped(job))
		ft_printf("[%d]%c  %.*s\t\t%s\n", job->jobc_id, job->jobc_last
		, ft_strlen("Running")
		, "Running", job->command);
	else
		ft_printf("[%d]%c  %.*s\t\t%s\n", job->jobc_id, job->jobc_last
		, ft_strlen(get_last_stop_status(job)) - 1
		, get_last_stop_status(job), job->command);
}

static int8_t	jobs_invalid_opt(u_int64_t opt)
{
	print_usage("42sh: jobs", opt & 0xFF, "jobs [-lp] [jobspec ...]");
	return (2);
}

int8_t			builtin_jobs(t_core *shell, t_process *process)
{
	t_lst		*job_list;
	t_job		*job;
	u_int64_t	opt;
	size_t		argc;
	size_t		i;

	argc = ft_tablen(process->av);
	job_list = shell->launched_jobs;
	i = skip_opt(process->av);
	if (shell->launched_jobs)
		update_status(shell);
	if ((opt = ft_get_options((int)argc, process->av, "lp")) & (1ULL << 63))
		return(jobs_invalid_opt(opt));
	while (i == argc && job_list)
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
