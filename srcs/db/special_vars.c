/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  special_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 11:28:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/02 11:34:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	update_sharp_var(t_core *shell)
{
	t_db	*db;
	char	*value;

	db = NULL;
	value = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "#", SPECIAL_VAR)) != NULL)
	{
		value = ft_itoa(ft_lstlen(shell->pos_vars));
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

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

int8_t	update_shell_name(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "0", SPECIAL_VAR)) != NULL)
	{
		value = ft_strdup("42sh");
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

int8_t	update_shell_flags(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "-", SPECIAL_VAR)) != NULL)
	{
		value = ft_strdup("himBH");
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

int8_t	update_exit_status(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "?", SPECIAL_VAR)) != NULL)
	{
		value = ft_itoa(shell->last_exit_status);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
