/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:10 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/16 18:32:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

static int8_t	hash_opt_parser(t_core *shell, int ac, t_process *process)
{
	static int8_t	(*hash_opt[5])() = {hash_l, hash_r, hash_p, hash_d, hash_t};
	u_int64_t		options;
	size_t			i;

	options = ft_get_options(ac, process->av, HASH_OPT);
	i = 0;
	while (i < 5)
	{
		if (options & (1ULL << (HASH_OPT[i] - 97)))
			return (hash_opt[i](shell, process, ac));
		i++;
	}
	print_usage("hash", options % 128, HASH_USAGE);
	return (SUCCESS);
}

int8_t			builtin_hash(t_core *shell, t_process *process)
{
	int		ac;

	ac = ft_tablen(process->av);
	if (ac > 1 && process->av[1][0] != '-')
	{
		hash_map_dispatcher(shell, process, H_DEF);
		return (SUCCESS);
	}
	if (ac == 1 || hash_opt_parser(shell, ac, process) == FAILURE)
		print_hash_map(shell, H_DEF);
	return (SUCCESS);
}
