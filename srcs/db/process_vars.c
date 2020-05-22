/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:51:00 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 15:14:31 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

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
	if (shell && (db = get_or_create_db(shell, "$", SPECIAL_VAR)) != NULL)
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
**	Update the $! special variable containing the pid of the last process
**	placed in background in $! special var
**		- Should be updated each time it changes
*/

int8_t	update_background_pid(t_core *shell)
{
	char		*value;
	t_job		*job;
	t_db		*db;

	db = NULL;
	value = NULL;
	job = get_job(shell->launched_jobs, "%%");
	if (shell && (db = get_or_create_db(shell, "!", SPECIAL_VAR)))
	{
		if (job)
			value = ft_itoa(job->pgid);
		else
			value = ft_strdup("0");
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
