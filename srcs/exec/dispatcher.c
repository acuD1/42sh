/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/05 02:53:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	dispatcher(t_core *shell, t_lst *jobs)
{
	t_lst	*ptr;
	int		status;

	ptr = jobs->process_list;
	status = 0;
	while (ptr != NULL)
	{
		if (ptr->type == P_PIPE && pipeline_exec(shell, &ptr) != SUCCESS)
			return (FAILURE);
		else
		{
			//EXPANSION
			exec_process(shell, ptr);
		}
		//CONDITIONS
	}
	return (SUCCESS);
}
