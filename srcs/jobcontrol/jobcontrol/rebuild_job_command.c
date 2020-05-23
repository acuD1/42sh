/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_job_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:31:19 by user42            #+#    #+#             */
/*   Updated: 2020/04/23 17:31:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*get_short_command(t_process *process)
{
	int		skip;

	if (ft_strncmp(process->command, "&& ", 3) == 0
		|| ft_strncmp(process->command, "|| ", 3) == 0)
		skip = 3;
	else if (ft_strncmp(process->command, "| ", 2) == 0)
		skip = 2;
	else
		skip = 0;
	return (process->command + skip);
}

void	rebuild_job_command(t_job *job)
{
	t_lst	*ptr;
	char	*tmp;

	ptr = job->process_list;
	ft_strdel(&(job->command));
	while (ptr)
	{
		if (ptr == job->process_list)
			tmp = ft_strjoin(job->command, get_short_command(ptr->content));
		else
		{
			tmp = ft_strjoin(job->command, " ");
			ft_strdel(&(job->command));
			job->command = tmp;
			tmp = ft_strjoin(job->command, ((t_process*)ptr->content)->command);
		}
		ft_strdel(&(job->command));
		job->command = tmp;
		ptr = ptr->next;
	}
}
