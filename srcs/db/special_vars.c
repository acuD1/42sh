/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:40:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:34:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update the $# special var. It contains the number of positional variables
**	($1 $2 $.. $n) equivalent to argc.
**		- Should be updated each time set is used to add positional vars.
*/

int8_t	update_sharp_var(t_core *shell)
{
	t_db	*db;
	char	*value;

	db = NULL;
	value = NULL;
	if (shell && (db = get_or_create_db(shell, "#", SPECIAL_VAR)) != NULL)
	{
		value = ft_itoa((int32_t)ft_lstlen(shell->pos_vars));
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update the $0 special variable containing the shell name.
**		- Should be exec. only one time at the shell startup.
*/

int8_t	update_shell_name(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	if (shell && (db = get_or_create_db(shell, "0", SPECIAL_VAR)) != NULL)
	{
		value = ft_strdup("42sh");
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update $- special variable, containing shell flags
**	(not fully fonctional, because what are those ?)
*/

int8_t	update_shell_flags(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	if (shell && (db = get_or_create_db(shell, "-", SPECIAL_VAR)) != NULL)
	{
		if (shell->opt & (1ULL << ('v' - 'a')
			&& shell->opt & (1ULL << ('c' - 'a'))))
			value = ft_strdup("cv");
		else if (shell->opt & (1ULL << ('v' - 'a')))
			value = ft_strdup("v");
		else if (shell->opt & (1ULL << ('c' - 'a')))
			value = ft_strdup("c");
		else
			value = ft_strdup("");
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update the $? special variable containing the last process exit status
**		- initialized at shell startup and updated each time a pipeline exits
*/

int8_t	update_exit_status(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	if (shell && (db = get_or_create_db(shell, "?", SPECIAL_VAR)) != NULL)
	{
		value = ft_itoa(shell->status);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
