/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:51:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/25 00:59:42 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	update_histfile(t_core *core)
{
	t_db	*db;
	char	*ptr;

	db = NULL;
	ptr = getlogin();
	if (core && ptr != NULL 
			&& (db = get_or_create_db(core, "HISTFILE", SET_VAR)) != NULL)
	{
		if (modify_db(db, ft_strjoinf(ft_strjoin("/Users/", ptr)
						, ft_strdup("/.pistash_history"), 4), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

int8_t	update_hist_size(t_core *core)
{
	t_db	*db;

	db = NULL;
	if (core && (db = get_or_create_db(core, "HISTSIZE", SET_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(HIST_SIZE), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

int8_t	update_histfile_size(t_core *core)
{
	t_db	*db;

	db = NULL;
	if (core && (db = get_or_create_db(core, "HISTFILESIZE", SET_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(HISTFILE_SIZE), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}
