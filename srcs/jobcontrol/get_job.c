/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:25:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:58:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static t_job	*get_last_job(t_lst *jobs)
{
	while (jobs)
	{
		if (((t_job*)jobs->content)->jobc_last == '+')
			return (jobs->content);
		jobs = jobs->next;
	}
	return (NULL);
}

t_job			*get_job_by_id(t_lst *jobs, int id)
{
	t_lst	*save;
	t_job	*ptr;

	save = jobs;
	while (jobs)
	{
		ptr = jobs->content;
		if ((id > 0 && ptr->jobc_id == id)
		|| (id < 0 && ptr->jobc_last == id + '0'))
			return (ptr);
		jobs = jobs->next;
	}
	if (id < 0)
		return (get_last_job(save));
	return (NULL);
}

static t_job	*get_job_by_name(t_lst *jobs, char *str)
{
	t_job	*ptr;
	size_t	i;

	while (jobs)
	{
		ptr = jobs->content;
		i = 0;
		while (str[i] == ptr->command[i])
		{
			i++;
			if (str[i] == 0)
				return (ptr);
		}
		jobs = jobs->next;
	}
	return (NULL);
}

t_job			*get_job(t_lst *jobs, char *str)
{
	t_job	*job;

	job = NULL;
	if (jobs == NULL)
		return (job);
	if (!str || ft_strcmp("%%", str) == 0)
		job = get_last_job(jobs);
	else if (str && str[0] == '%' && (str[1] == '-' || str[1] == '+'))
		job = get_job_by_id(jobs, str[1] - '0');
	else if (str && str[0] == '%')
		job = get_job_by_id(jobs, ft_atoi(str + 1));
	else if (str)
		job = get_job_by_name(jobs, str);
	return (job);
}
