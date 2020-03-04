/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:34:39 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/04 21:39:38 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	print_shell_usage(int option, int fd)
{
	if (fd == STDERR_FILENO)
		ft_dprintf(fd, "42sh: -%c: invalid option\n", option);
	ft_dprintf(fd, "Usage: 42sh [option] ...\n");
	ft_dprintf(fd, "Shell options:\n\t-vh or -c command\n");
}

static void	opt_h(int ac, char **av, t_core *shell)
{
	(void)ac;
	(void)av;
	ft_dprintf(STDERR_FILENO, "42sh, version %d.%d.%d\n",
		shell->build.release, shell->build.version, shell->build.patch);
	print_shell_usage(0, STDOUT_FILENO);
	quit_shell(shell, EXIT_SUCCESS, FALSE);
}

static void	opt_v(int ac, char **av, t_core *shell)
{
	(void)ac;
	(void)av;
	ft_dprintf(STDOUT_FILENO, "42sh, version %d.%d.%d\n",
		shell->build.release, shell->build.version, shell->build.patch);
}

static void	opt_c(int ac, char **av, t_core *shell)
{
	(void)ac;
	if (!av[2])
	{
		ft_dprintf(STDERR_FILENO, "42sh: -c: option requires an argument\n");
		quit_shell(shell, 2, FALSE);
	}
	shell->is_interactive = FALSE;
	shell->term.buffer = ft_strdup(av[2]);
	lexer_parser_analyzer(shell);
	if (task_master(shell) != SUCCESS)
		return (quit_shell(shell, EXIT_FAILURE, FALSE));
	quit_shell(shell, EXIT_SUCCESS, FALSE);
}

void		get_opt(int ac, char **av, t_core *shell)
{
	size_t		i;
	u_int64_t	opt;

	if (!av[1])
		return ;
	opt = ft_get_options(ac, av, SHELL_OPT);
	if (opt & (1ULL << 63))
	{
		print_shell_usage(opt % 128, STDERR_FILENO);
		quit_shell(shell, EXIT_FAILURE, FALSE);
	}
	i = 0;
	if (opt & (1ULL << ('h' - 97)))
		opt_h(ac, av, shell);
	if (opt & (1ULL << ('v' - 97)))
		opt_v(ac, av, shell);
	if (opt & (1ULL << ('c' - 97)))
		opt_c(ac, av, shell);
}
