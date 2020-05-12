/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/05/12 11:14:56 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static int8_t	check_n_args(size_t i, size_t argc)
{
	if ((argc - i) >= 2)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: too many arguments\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	get_opt_cd(t_process *process, char *option, size_t *i)
{
	size_t	j;

	j = 1;
	while (process->av[*i][j])
	{
		*option = process->av[*i][j];
		if (*option != 'P' && *option != 'L' && *option != 0)
		{
			print_usage("cd", (u_int8_t)(*option), CD_USAGE);
			return (FAILURE);
		}
		j++;
	}
	(*i)++;
	return (SUCCESS);
}

static int8_t	cd_opt_parser
	(t_process *process, char *option, size_t *i, size_t argc)
{
	while (process->av[*i])
	{
		if (ft_strequ(process->av[*i], "--"))
		{
			(*i)++;
			if (check_n_args(*i, argc) == SUCCESS)
				break ;
			else
				return (FAILURE);
		}
		if (process->av[*i][0] == '-' && process->av[*i][1])
		{
			if (get_opt_cd(process, option, i) == SUCCESS)
				continue ;
			else
				return (FAILURE);
		}
		if (check_n_args(*i, argc) != SUCCESS)
			return (FAILURE);
		if (!process->av[*i + 1])
			break ;
		(*i)++;
	}
	return (SUCCESS);
}

static int8_t	cd_handler
	(t_core *shell, t_process *process, size_t i, char options)
{
	char	pwd[MAX_PATH + 1];

	ft_bzero(pwd, MAX_PATH + 1);
	if (!process->av[i])
		return (cd_home(shell));
	if (process->av[i][0] == '-' && !process->av[i][1])
	{
		if (options == 'P')
			shell->cd.no_symbolic = TRUE;
		return (cd_oldpwd(shell));
	}
	if (options == 'L')
		return (change_dir(shell, process->av[i]));
	if (options == 'P')
	{
		if (getcwd(pwd, MAX_PATH) == NULL)
			shell->cd.pwd_error = TRUE;
		shell->cd.no_symbolic = TRUE;
		return (change_dir(shell, process->av[i]));
	}
	return (change_dir(shell, process->av[i]));
}

int8_t			builtin_cd(t_core *shell, t_process *process)
{
	char	tmp[MAX_PATH + 1];
	char	option;
	size_t	argc;
	size_t	i;

	ft_bzero(tmp, MAX_PATH + 1);
	shell->cd.no_symbolic = FALSE;
	option = 0;
	i = 1;
	argc = ft_tablen(process->av);
	if (argc == 1)
		return (cd_home(shell));
	if (ft_strcmp(process->av[1], "-")
		== 0 && !process->av[1][1] && !process->av[2])
		return (cd_oldpwd(shell));
	if (cd_opt_parser(process, &option, &i, argc) != SUCCESS)
		return (1);
	return (cd_handler(shell, process, i, option));
}
