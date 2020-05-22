/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobc_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 20:07:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/19 23:08:46 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		attr_jobc_id(t_core *shell, t_job *job)
{
	t_lst	*jobs;
	t_job	*ptr;
	int		c;

	c = 0;
	jobs = shell->launched_jobs;
	while (jobs)
	{
		ptr = ((t_job*)jobs->content);
		if (ptr != job && ptr->jobc_id > c)
			c = ptr->jobc_id;
		ptr->jobc_last = (ptr->jobc_last == '+') ? '-' : ' ';
		jobs = jobs->next;
	}
	job->jobc_id = c + 1;
	job->jobc_last = '+';
}

static int	update_job_plus(t_lst *jobs, int max_id, int less_id)
{
	t_job	*job;

	if (!(job = get_job_by_id(jobs, (less_id > 0) ? less_id : max_id)))
		return (0);
	job->jobc_last = '+';
	return (job->jobc_id);
}

static void	update_job_less(t_lst *jobs, int max_id, int plus_id)
{
	t_job	*job;

	if (!(job = get_job_by_id(jobs, (plus_id == max_id) ? max_id - 1 : max_id)))
		return ;
	job->jobc_last = '-';
}

int			update_jobs(t_lst *jobs)
{
	t_lst	*ptr;
	t_job	*job;
	int		plus;
	int		less;
	int		c;

	c = 0;
	plus = 0;
	less = 0;
	ptr = jobs;
	while (ptr)
	{
		job = ((t_job*)ptr->content);
		c = (c < job->jobc_id) ? job->jobc_id : c;
		plus = (job->jobc_last == '+') ? job->jobc_id : plus;
		less = (job->jobc_last == '-') ? job->jobc_id : less;
		job->jobc_last = ' ';
		ptr = ptr->next;
	}
	if (c > 0 && plus == 0)
		plus = update_job_plus(jobs, c, less);
	if (c > 1 && less == 0)
		update_job_less(jobs, c, plus);
	return (c + 1);
}
