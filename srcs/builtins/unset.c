/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 03:59:34 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 01:21:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	parse_unset(int argc, char **argv)
{
	u_int64_t	options;

	options = ft_get_options(argc, argv, "");
	if (options & (1ULL << 63))
	{
		print_usage("unset", options % 128, "unset [name ...]");
		return (2);
	}
	return (SUCCESS);
}

int8_t			builtin_unset(t_core *shell, t_process *process)
{
	int		parsing_ret;
	int		argc;
	int		ret;
	int		i;

	ret = 0;
	argc = ft_tablen(process->av);
	i = (argc > 1 && process->av[1][0] != '-') ? 1 : 2;
	if ((parsing_ret = parse_unset(argc, process->av) > 0))
		return (parsing_ret);
	while (i < argc)
	{
		if (check_invalid_identifiers(process->av[i], "") != SUCCESS)
		{
			ret = 1;
			dprintf(STDERR_FILENO
			, "42sh: export: `%s': not a valid identifier\n", process->av[i]);
		}
		else
			del_db(shell, process->av[i]);
		i++;
	}
	return (ret);
}
