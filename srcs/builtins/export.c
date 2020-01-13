/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/13 08:32:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	parse_export(int argc, char **argv)
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

static int8_t	export(t_core *shell, char *arg, int *ret)
{
	t_db	*db;
	char	*str;
	int		len;

	len = ft_strclen(arg, '=');
	str = ft_strsub(arg, 0, len);
	if (ft_strequ(str, "PATH") == TRUE)
		free_hash_map(&shell->hash); // Need testing, also we need it when we assign variable without export
	if (str && (check_invalid_identifiers(str, "=")
			|| ft_isdigit(arg[0]) != SUCCESS))
	{
		*ret = 1;
		dprintf(STDERR_FILENO, "42sh: export: `%s': not a valid identifier\n", arg);
		ft_strdel(&str);
		return (SUCCESS);
	}
	else if (!str || !(db = get_or_create_db(shell, str, ENV_VAR)))
	{
		ft_strdel(&str);
		return (FAILURE);
	}
	ft_strdel(&str);
	str = ((int)ft_strlen(arg) > len) ? ft_strdup(arg + len + 1) : NULL;
	modify_db(db, str, ENV_VAR);
	return (SUCCESS);
}

int8_t	builtin_export(t_core *shell, t_process *process)
{
	int		argc;
	int		ret;
	int		i;

	argc = ft_tablen(process->av);
	i = (argc > 1 && process->av[1][0] != '-') ? 1 : 2;
	if ((ret = parse_export(argc, process->av)) != SUCCESS)
		return (ret);
	ret = 0;
	while (i < argc)
	{
		if (export(shell, process->av[i], &ret) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (ret);
}
