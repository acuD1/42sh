/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:34:39 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/25 13:45:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_shell_usage(int option, int fd)
{
	if (fd == STDERR_FILENO)
		dprintf(fd, "42sh: -%c: invalid option\n", option);
	dprintf(fd, "Usage: 42sh [option] ...\n");
	dprintf(fd, "Shell options:\n\t-vh or -c command\n");
}

void	opt_h(int ac, char **av, t_core *shell)
{
	(void)ac;
	(void)av;
	dprintf(STDOUT_FILENO, "42sh, version %d.%d.%d\n",
		shell->build.release, shell->build.version, shell->build.patch);
	print_shell_usage(0, STDOUT_FILENO);
}

void	opt_v(int ac, char **av, t_core *shell)
{
	(void)ac;
	(void)av;
	dprintf(STDOUT_FILENO, "42sh, version %d.%d.%d\n",
		shell->build.release, shell->build.version, shell->build.patch);
}

void	opt_c(int ac, char **av, t_core *shell)
{
	(void)ac;
	if (!av[2])
	{
		dprintf(STDERR_FILENO, "42sh: -c: option requires an argument\n");
		return ;
	}
	shell->term.buffer = ft_strdup(av[2]);
	lexer_parser_analyzer(shell);
	if (task_master(shell) != SUCCESS)
		return (quit_shell(shell, EXIT_FAILURE, FALSE, NOI_MODE));
	quit_shell(shell, EXIT_SUCCESS, FALSE, NOI_MODE);
}

void	get_opt(int ac, char **av, t_core *shell)
{
	static void	(*shell_opt[3])() = {opt_v, opt_h, opt_c};
	size_t		i;
	u_int64_t	opt;

	if (!av[1])
		return ;
	opt = get_options(ac, av, SHELL_OPT);
	if (opt & (1ULL << 63))
	{
		print_shell_usage(opt % 128, STDERR_FILENO);
		quit_shell(shell, EXIT_FAILURE, FALSE, OPT_MODE);
	}
	i = 0;
	while (i < 3)
	{
		if (opt & (1ULL << (SHELL_OPT[i] - 97)))
		{
			shell_opt[i](ac, av, shell);
			quit_shell(shell, EXIT_SUCCESS, FALSE, OPT_MODE);
		}
		i++;
	}
}
