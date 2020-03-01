/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/01 23:46:13 by mpivet-p         ###   ########.fr       */
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

static int8_t	export(t_core *shell, const char *arg, int *ret, u_int64_t opt)
{
	t_db	*db;
	char	*str;
	int		len;

	len = ft_strclen(arg, '=');
	str = ft_strsub(arg, 0, len);
	export_hash_handler(shell, str);
	if (str && (check_invalid_identifiers(str, "=") || ft_isdigit(arg[0]) != 0))
	{
		*ret = 1;
		dprintf(STDERR_FILENO
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
	str = ((int)ft_strlen(arg) > len) ? ft_strdup(arg + len + 1) : NULL;
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
				printf("export %s=\"%s\"\n", ptr->key, ptr->value);
			else
				printf("export %s\n", ptr->key);
		}
		db = db->next;
	}
}

int8_t			builtin_export(t_core *shell, t_process *process)
{
	u_int64_t	opt;
	int			argc;
	int			ret;
	int			i;

	argc = ft_tablen(process->av);
	i = (argc > 1 && process->av[1][0] != '-') ? 1 : 2;
	if (i == argc + 1)
	{
		export_display(shell);
		return (0);
	}
	if ((ret = parse_export(argc, process->av, &opt)) != SUCCESS)
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
