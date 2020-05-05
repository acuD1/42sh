/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:30:02 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

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

static int8_t	export
	(t_core *shell, const char *arg, int8_t *ret, u_int64_t opt)
{
	t_db	*db;
	char	*str;
	size_t	len;

	len = ft_strclen(arg, '=');
	if (!(str = ft_strsub(arg, 0, len)))
		return (FAILURE);
	if (ft_strncmp(arg, "PATH=", 5) == 0)
		free_hash_map(&shell->hash);
	if (check_invalid_identifiers(str, "_") || ft_isdigit(arg[0]) != 0)
	{
		*ret = 1;
		ft_dprintf(STDERR_FILENO
		, "42sh: export: `%s': not a valid identifier\n", arg);
		ft_strdel(&str);
		return (SUCCESS);
	}
	db = get_or_create_db(shell, str, 0);
	ft_strdel(&str);
	str = (ft_strchr(arg, '=')) ? ft_strdup(arg + len + 1) : NULL;
	if (opt == 0 && ft_strchr(arg, '='))
		modify_db(db, str, db->type | EXPORT_VAR | INTERNAL_VAR);
	else
		modify_db(db, str, db->type | EXPORT_VAR);
	return (db ? SUCCESS : FAILURE);
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

static void		export_envp(t_core *shell, t_process *process)
{
	char	*value;
	char	*key;
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	while (process->envp[i])
	{
		str = process->envp[i];
		len = ft_strclen(str, '=');
		key = ft_strsub(str, 0, len);
		value = ft_strsub(str, (unsigned int)len + 1, ft_strlen(str) - len);
		edit_var(shell, key, value, INTERNAL_VAR | EXPORT_VAR);
		ft_strdel(&key);
		i++;
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
		export_display(shell);
	export_envp(shell, process);
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
