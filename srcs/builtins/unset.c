/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 03:59:34 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/02 02:53:01 by mpivet-p         ###   ########.fr       */
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
	return (SUCCESS);
}

int8_t	builtin_unset(t_core *shell)
{
	int		parsing_ret;
	int		argc;
	int		ret;
	int		i;

	ret = 0;
	argc = ft_tablen(shell->tokens);
	i = (argc > 1 && shell->tokens[1][0] != '-') ? 1 : 2;
	if ((parsing_ret = parse_unset(argc, shell->tokens) > 0))
		return (parsing_ret);
	while (i < argc)
	{
		if (check_invalid_identifiers(shell->tokens[i], "") != SUCCESS)
		{
			ret = 1;
			dprintf(STDERR_FILENO, "42sh: export: `%s': not a valid identifier\n", shell->tokens[i]);
		}
		else
			del_db(shell, shell->tokens[i]);
		i++;
	}
	return (ret);
}
