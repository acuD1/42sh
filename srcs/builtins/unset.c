/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 03:59:34 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/30 03:32:15 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	parse_unset(int argc, char **argv)
{
	u_int64_t	options;

	options = get_options(argc, argv, "");
	if (options & (1ULL << 63))
	{
		print_usage("unset", options % 128, "unset [name ...]");
		return (2);
	}
	if (argc == 1)
		return (1);
	return (SUCCESS);
}

int8_t	builtin_unset(t_core *shell)
{
	int		parsing_ret;
	int		i;
	int		argc;

	argc = ft_tablen(shell->tokens);
	parsing_ret = parse_unset(argc, shell->tokens);
	i = 1;
	if (parsing_ret > 0)
		return (parsing_ret - 1);
	while (i < argc)
	{
		del_db(shell, shell->tokens[i]);
		i++;
	}
	return (SUCCESS);
}
