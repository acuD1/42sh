/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:25:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/19 22:57:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static t_job	*get_last_job(t_lst *jobs)
{
	while (jobs)
	{
		if (jobs->next == NULL)
			return (jobs->content);
		jobs = jobs->next;
	}
	return (NULL);
}

t_job			*get_job_by_id(t_lst *jobs, int id)
{
	t_job	*ptr;

	while (jobs)
	{
		ptr = jobs->content;
		if (ptr->jobc_id == id)
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

t_job			*get_job(t_lst *jobs, char *str)
{
	t_job	*job;

	job = NULL;
	if (!jobs)
		return (job);
	if (!str || ft_strcmp("%%", str) == 0)
		job = get_last_job(jobs);
	else if (str && str[0] == '%')
		job = get_job_by_id(jobs, ft_atoi(str + 1));
	else
		job = get_job_by_name(jobs, str);
	return (job);
}
