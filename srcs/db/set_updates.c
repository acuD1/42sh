/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:56:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/29 02:56:31 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "sh42.h"

/*
**	Create IFS set variable (Input Field Separator)
*/

int8_t	update_ifs(t_core *shell)
{
	t_db	*db;

	db = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "IFS", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_strdup("' \t\n'"), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
**	Create TERM set variable if not existing (default value = dumb)
*/

int8_t	create_term(t_core *shell)
{
	if (shell != NULL && search_db(shell->env, "TERM") == NULL)
	{
		if (ft_lstappend(&(shell->env), ft_lstnew(
				fetch_db(&(shell->db), "TERM=dumb", INTERNAL_VAR), sizeof(t_db))) != NULL)
			return (SUCCESS);
	}
	return (SUCCESS);
}

/*
**	Create LINES and COLUMNS (set variables) with the terminal width and height
*/

int8_t	update_termsize(t_core *shell)
{
	struct winsize	ws;
	t_db			*db;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	if (shell != NULL && (db = get_or_create_db(shell, "LINES", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(ws.ws_row), 0) == NULL)
			return (FAILURE);
	}
	if (shell && (db = get_or_create_db(shell, "COLUMNS", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_itoa(ws.ws_col), 0) == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}
