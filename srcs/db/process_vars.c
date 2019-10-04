/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 02:55:33 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/04 08:24:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update or create $$ special variable, containing the pid of the program
**		- Should only be executed at shell startup
*/

int8_t	update_process_id(t_core *shell)
{
	pid_t	pid;
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	pid = -1;
	if (shell != NULL && (db = get_or_create_db(shell, "$", SPECIAL_VAR)) != NULL)
	{
		if ((pid = getpid()) >= 0)
			value = ft_itoa((int)pid);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	TMP function to get last process placed in background (asynchronous or bg)
*/

t_process	*get_last_job(t_core *shell)
{
	t_lst	*ptr;
	
	ptr = shell->jobs;
	while (ptr)
	{
		if (((t_process*)ptr->content)->bck_order == 0)
			return ((t_process*)ptr->content);
		ptr = ptr->next;
	}
	return (NULL);
}

/*
**	Update the $! special variable containing the pid of the last process
**	placed in background in $! special var
**		- Should be updated each time it changes
*/

int8_t	update_backgroud_pid(t_core *shell)
{
	char		*value;
	t_db		*db;
	t_process	*ptr;

	db = NULL;
	value = NULL;
	ptr = get_last_job(shell);
	if (shell && ptr && (db = get_or_create_db(shell, "!", SPECIAL_VAR)))
	{
		value = ft_itoa((int)ptr->pid);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
