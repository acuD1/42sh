/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 22:37:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/29 04:32:04 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	parse_set(int argc, char **argv)
{
	u_int64_t	options;

	options = get_options(argc, argv, "");
	if (options & (1ULL << 63))
	{
		print_usage("set", options % 128, "set");
		return (3);
	}
	if (argc > 1)
		return (1);
	return (SUCCESS);
}

void	print_internal_vars(t_core *shell)
{
	t_lst	*ptr;

	ptr = shell->env;
	while (ptr != NULL)
	{
		if (((t_db*)ptr->content)->type & ENV_VAR
				|| ((t_db*)ptr->content)->type & SET_VAR)
		{
			printf("%s=%s\n", ((t_db*)ptr->content)->key
					, ((t_db*)ptr->content)->value); //ADD FT_
		}
		ptr = ptr->next;
	}
}

int8_t	builtin_set(int argc, char **argv, t_core *shell)
{
	int8_t	parsing_ret;

	parsing_ret = parse_set(argc, argv);
	if (parsing_ret > 0)
		return (parsing_ret - 1);
	print_internal_vars(shell);
	return (SUCCESS);
}
