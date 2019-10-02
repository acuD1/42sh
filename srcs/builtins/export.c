/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/02 04:32:04 by mpivet-p         ###   ########.fr       */
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

int8_t	export(t_core *shell, char *arg)
{
	t_db	*db;
	char	*str;
	int		len;

	db = NULL;
	len = ft_strclen(arg, '=');
	str = ft_strsub(arg, 0, len);
	db = get_or_create_db(shell, str, ENV_VAR);
	ft_strdel(&str);
	if (!db)
		return (FAILURE);
	str = ((int)ft_strlen(arg) > len) ? ft_strdup(arg + len + 1) : NULL;
	modify_db(db, str, ENV_VAR);
	return (SUCCESS);
}

int8_t	builtin_export(t_core *shell)
{
	int		parsing_ret;
	int		argc;
	int		ret;
	int		i;

	i = 1;
	ret = 0;
	argc = ft_tablen(shell->tokens);
	if ((parsing_ret = parse_export(argc, shell->tokens)) != SUCCESS)
		return (parsing_ret);
	while (i < argc)
	{
		if (check_invalid_identifiers(shell->tokens[i], "=")
				|| ft_isdigit(shell->tokens[i][0]) != SUCCESS)
		{
			ret = 1;
			dprintf(STDERR_FILENO, "pistash: export: `%s': not a valid identifier\n", shell->tokens[i]);
		}
		else
			export(shell, shell->tokens[i]);
		i++;
	}
	return (ret);
}
