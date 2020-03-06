/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/05 04:18:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	parse_export(int argc, char **argv, u_int64_t *options)
{
	*options = ft_get_options(argc, argv, "p");
	if (*options & (1ULL << 63))
	{
		print_usage("export", *options % 128, "unset [name ...]");
		return (2);
	}
	return (SUCCESS);
}

static void		export_hash_handler(t_core *shell, const char *str)
{
	if (ft_strequ(str, "PATH") == TRUE)
		free_hash_map(&shell->hash);
}

static int8_t	export
	(t_core *shell, const char *arg, int8_t *ret, u_int64_t opt)
{
	t_db	*db;
	char	*str;
	size_t	len;

	len = ft_strclen(arg, '=');
	str = ft_strsub(arg, 0, len);
	export_hash_handler(shell, str);
	if (str && (check_invalid_identifiers(str, "=") || ft_isdigit(arg[0]) != 0))
	{
		*ret = 1;
		ft_dprintf(STDERR_FILENO
		, "42sh: export: `%s': not a valid identifier\n", arg);
		ft_strdel(&str);
		return (SUCCESS);
	}
	else if (!str || !(db = get_or_create_db(shell, str, EXPORT_VAR
			| ((opt == 0 && ft_strchr(arg, '=')) ? INTERNAL_VAR : 0))))
	{
		ft_strdel(&str);
		return (FAILURE);
	}
	ft_strdel(&str);
	str = (ft_strlen(arg) > len) ? ft_strdup(arg + len + 1) : NULL;
	modify_db(db, str, db->type | EXPORT_VAR);
	return (SUCCESS);
}

static void		export_display(t_core *shell)
{
	t_lst	*db;
	t_db	*ptr;

	db = shell->env;
	while (db)
	{
		ptr = ((t_db*)db->content);
		if (ptr->type & EXPORT_VAR)
		{
			if (ptr->value)
				ft_printf("export %s=\"%s\"\n", ptr->key, ptr->value);
			else
				ft_printf("export %s\n", ptr->key);
		}
		db = db->next;
	}
}

int8_t			builtin_export(t_core *shell, t_process *process)
{
	u_int64_t	opt;
	size_t		argc;
	size_t		i;
	int8_t		ret;

	argc = ft_tablen(process->av);
	i = (argc > 1 && process->av[1][0] != '-') ? 1 : 2;
	if (i == argc + 1)
	{
		export_display(shell);
		return (0);
	}
	if ((ret = parse_export((int)argc, process->av, &opt)) != SUCCESS)
		return (ret);
	ret = 0;
	while (i < argc)
	{
		if (export(shell, process->av[i], &ret, opt) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (ret);
}
