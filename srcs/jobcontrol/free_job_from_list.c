/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job_from_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:24:57 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 15:35:29 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

void	free_job(t_lst **job_list, t_lst *job)
{
	t_lst	*ptr;

	ptr = *job_list;
	if (*job_list != job)
	{
		while (ptr && ptr->next != job)
			ptr = ptr->next;
		if (ptr)
			ptr->next = job->next;
	}
	else
	{
		*job_list = job->next;
	}
	if (job)
	{
		free_process_list(&(((t_job*)job->content)->process_list));
		ft_strdel(&(((t_job*)job->content)->command));
		free(job->content);
		free(job);
	}
}
