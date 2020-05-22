/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:18:33 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 17:03:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/*
**	Update [INTERNAL_VAR] HISTFILE, continaining the place of the history file
**		- Should only be executed at shell startup
*/

int8_t	update_histfile(t_core *shell)
{
	struct passwd	*pw;
	const char		*home_dir;
	t_db			*db;
	char			*value;

	pw = getpwuid(getuid());
	home_dir = pw->pw_dir;
	db = NULL;
	value = NULL;
	if (shell && home_dir != NULL
			&& (db = get_or_create_db(shell, "HISTFILE", INTERNAL_VAR)) != NULL)
	{
		value = ft_strjoin(home_dir, "/.42sh_history");
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
