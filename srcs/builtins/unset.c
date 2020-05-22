/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 03:59:34 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:52:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static int8_t	parse_unset(size_t argc, char **argv)
{
	u_int64_t	options;

	options = ft_get_options((int)argc, argv, "");
	if (options & (1ULL << 63))
	{
		print_usage("unset", options % 128, "unset [name ...]");
		return (2);
	}
	return (SUCCESS);
}

static void		unset_hash_handler(t_core *shell, const char *str)
{
	if (ft_strequ(str, "PATH") == TRUE)
		free_hash_map(&shell->hash);
}

int8_t			builtin_unset(t_core *shell, t_process *process)
{
	int8_t	parsing_ret;
	size_t	argc;
	int8_t	ret;
	size_t	i;

	ret = 0;
	argc = ft_tablen(process->av);
	i = (argc > 1 && process->av[1][0] != '-') ? 0 : 1;
	if ((parsing_ret = parse_unset(argc, process->av) > 0))
		return (parsing_ret);
	while (++i < argc)
	{
		if (check_invalid_identifiers(process->av[i], "") != SUCCESS)
		{
			ret = 1;
			ft_dprintf(STDERR_FILENO
			, "42sh: unset: `%s': not a valid identifier\n", process->av[i]);
		}
		else
		{
			unset_hash_handler(shell, process->av[i]);
			del_db(shell, process->av[i]);
		}
	}
	return (ret);
}
