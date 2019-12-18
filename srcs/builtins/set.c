/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 22:37:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/18 09:39:56 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	parse_set(int argc, char **argv)
{
	u_int64_t	options;

	options = get_options(argc, argv, "");
	if (options & (1ULL << 63))
	{
		print_usage("set", options % 128, "set [arg ...]");
		return (2);
	}
	return (SUCCESS);
}

static void		print_internal_vars(t_core *shell)
{
	t_lst	*ptr;

	ptr = shell->env;
	while (ptr != NULL)
	{
		if (((t_db*)ptr->content)->type & ENV_VAR
				|| ((t_db*)ptr->content)->type & INTERNAL_VAR)
		{
			dprintf(STDOUT_FILENO, "%s=%s\n", ((t_db*)ptr->content)->key
					, ((t_db*)ptr->content)->value); //ADD FT_
		}
		ptr = ptr->next;
	}
}

static int8_t	new_positional_var(t_core *shell, char *arg, int count)
{
	shell->db.key = ft_itoa(count);
	shell->db.value = ft_strdup(arg);
	shell->db.type = SPECIAL_VAR;
	if (!shell->db.key || !shell->db.value || ft_lstappend(&shell->pos_vars
				, ft_lstnew(&shell->db, sizeof(t_db))) == NULL)
	{
		ft_strdel(&(shell->db.key));
		ft_strdel(&(shell->db.value));
		return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	get_positional_vars(t_core *shell, t_process *process, int argc)
{
	int		i;

	i = (process->av[1][0] != '-') ? 1 : 2;
	free_env(shell->pos_vars);
	shell->pos_vars = NULL;
	while (i < argc)
	{
		if (new_positional_var(shell, process->av[i], i) != SUCCESS)
			return (FAILURE);
		i++;
	}
	if (update_sharp_var(shell) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			builtin_set(t_core *shell, t_process *process)
{
	int8_t	parsing_ret;
	int		argc;

	argc = ft_tablen(process->av);
	if ((parsing_ret = parse_set(argc, process->av)) > 0)
		return (parsing_ret);
	if (argc == 1)
	{
		print_internal_vars(shell);
	}
	else if (get_positional_vars(shell, process, argc) != SUCCESS)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
