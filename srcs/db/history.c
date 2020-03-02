/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:18:33 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/02 14:42:50 by mpivet-p         ###   ########.fr       */
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
		value = ft_strjoinf(ft_strjoinf("/Users/", ptr, 2)
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
	if (shell
		&& (db = get_or_create_db(shell, "HISTSIZE", INTERNAL_VAR)) != NULL)
	{
		value = ft_itoa(HIST_SIZE);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update [INTERNAL_VAR] HISTFILESIZE containing the maxsize of the hist file
**		- Should only be executed at shell startup
*/

int8_t	update_histfile_size(t_core *shell)
{
	t_db	*db;
	char	*value;

	db = NULL;
	value = NULL;
	if (shell
		&& (db = get_or_create_db(shell, "HISTFILESIZE", INTERNAL_VAR)) != NULL)
	{
		value = ft_itoa(HISTFILE_SIZE);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
