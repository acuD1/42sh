/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:56:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/23 21:16:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "sh42.h"

/*
**	Create IFS set variable (Input Field Separator)
*/

int8_t	update_ifs(t_core *core)
{
	t_db	*db;

	db = NULL;
	if (core != NULL && (db = get_or_create_db(core, "IFS", SET_VAR)) != NULL)
	{
		if (modify_db(db, ft_strdup("' \t\n'"), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
**	Create TERM set variable if not existing (default value = dumb)
*/

int8_t	create_term(t_core *core)
{
	if (core != NULL && search_db(core->env, "TERM") == NULL)
	{
		if (ft_lstappend(&(core->env), ft_lstnew(
				fetch_db(&(core->db), "TERM=dumb", SET_VAR), sizeof(t_db))) != NULL)
			return (SUCCESS);
	}
	return (SUCCESS);
}

/*
**	Create LINES and COLUMNS (set variables) with the terminal width and height
*/

int8_t	update_termsize(t_core *core)
{
	struct winsize	ws;
	t_db			*db;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	if (core != NULL && (db = get_or_create_db(core, "LINES", SET_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(ws.ws_row), 0) == NULL)
			return (FAILURE);
	}
	if (core && (db = get_or_create_db(core, "COLUMNS", SET_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(ws.ws_col), 0) == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}
