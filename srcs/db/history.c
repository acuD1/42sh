/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:51:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/29 02:55:55 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update [SET] HISTFILE, continaining the place of the history file
*/

int8_t	update_histfile(t_core *shell)
{
	t_db	*db;
	char	*ptr;

	db = NULL;
	ptr = getlogin();
	if (shell && ptr != NULL 
			&& (db = get_or_create_db(shell, "HISTFILE", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_strjoinf(ft_strjoin("/Users/", ptr)
						, ft_strdup("/.pistash_history"), 4), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
**	Update [SET] HISTSIZE containing the max size of the history
*/

int8_t	update_hist_size(t_core *shell)
{
	t_db	*db;

	db = NULL;
	if (shell && (db = get_or_create_db(shell, "HISTSIZE", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(HIST_SIZE), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
**	Update [SET] HISTFILESIZE containing the max size of the history file
*/

int8_t	update_histfile_size(t_core *shell)
{
	t_db	*db;

	db = NULL;
	if (shell && (db = get_or_create_db(shell, "HISTFILESIZE", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(HISTFILE_SIZE), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}
