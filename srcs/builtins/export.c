/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/30 05:26:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	parse_export(int argc, char **argv)
{
	u_int64_t	options;

	options = get_options(argc, argv, "");
	if (options & (1ULL << 63))
	{
		print_usage("export", options % 128, "unset [name ...]");
		return (2);
	}
	return (SUCCESS);
}

int		check_export_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i] == '=')
			return (i);
		if (ft_isalnum(arg[i]) != SUCCESS)
			return (-1);
		i++;
	}
	return (0);
}

int8_t	export(t_core *shell, char *arg)
{
	t_db	*db;
	char	*key;
	int		i;

	db = NULL;
	key = NULL;
	if ((i = check_export_arg(arg)) < 0)
	{
		dprintf(STDERR_FILENO, "pistash: export: `%s': not a valid identifier\n", arg);
		return (FAILURE);
	}
	if (!(key = (i == 0) ? ft_strdup(arg) : ft_strsub(arg, 0, i)))
		return (FAILURE);
	db = get_or_create_db(shell, key, ENV_VAR);
	ft_strdel(&key);
	if (!db)
		return (FAILURE);
	modify_db(db, (i != 0) ? ft_strdup(arg + i + 1) : NULL, ENV_VAR);
	return (SUCCESS);
}

int8_t	builtin_export(t_core *shell)
{
	int		parsing_ret;
	int		i;
	int		argc;

	argc = ft_tablen(shell->tokens);
	parsing_ret = parse_export(argc, shell->tokens);
	i = 1;
	if (parsing_ret > 0)
		return (parsing_ret);
	while (i < argc)
	{
		export(shell, shell->tokens[i]);
		i++;
	}
	return (SUCCESS);
}
