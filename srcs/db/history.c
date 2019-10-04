/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:51:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/04 08:25:11 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update [INTERNAL_VAR] HISTFILE, continaining the place of the history file
**		- Should only be executed at shell startup
*/

int8_t	update_histfile(t_core *shell)
{
	t_db	*db;
	char	*ptr;
	char	*value;

	db = NULL;
	ptr = getlogin();
	value = NULL;
	if (shell && ptr != NULL 
			&& (db = get_or_create_db(shell, "HISTFILE", INTERNAL_VAR)) != NULL)
	{
		value = ft_strjoinf(ft_strjoin("/Users/", ptr)
				, ft_strdup("/.42sh_history"), 4);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update [INTERNAL_VAR] HISTSIZE containing the max size of the history
**		- Should only be executed at shell startup
*/

int8_t	update_hist_size(t_core *shell)
{
	t_db	*db;
	char	*value;

	db = NULL;
	value = NULL;
	if (shell && (db = get_or_create_db(shell, "HISTSIZE", INTERNAL_VAR)) != NULL)
	{
		value = ft_itoa(HIST_SIZE);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update [INTERNAL_VAR] HISTFILESIZE containing the max size of the history file
**		- Should only be executed at shell startup
*/

int8_t	update_histfile_size(t_core *shell)
{
	t_db	*db;
	char	*value;

	db = NULL;
	value = NULL;
	if (shell && (db = get_or_create_db(shell, "HISTFILESIZE", INTERNAL_VAR)) != NULL)
	{
		value = ft_itoa(HISTFILE_SIZE);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
