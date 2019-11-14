/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/08 02:20:29 by mpivet-p         ###   ########.fr       */
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
