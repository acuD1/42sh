/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/22 14:15:11 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	ft_bzero(&shell, sizeof(t_core));

	/* Options output */
	print_opt(&shell, ac, av);

	/* initializing shell */
	init_shell(&shell, av, environ);

	/* Everything else will happen here */
	if (shell.is_interactive)
		load_prompt(&shell);
	else
		while (ft_getnextline(STDIN_FILENO, &(shell.cmd_line.buffer)))
			load_noi_mode(&shell);
	ft_strdel(&(shell.cmd_line.buffer));

	/* FREE Should be moved to quit_shell */
	free_env(shell.env);
	//free_env(shell.pos_vars);
	free_hash_map(&shell.hash);			// For now here ..
	return (EXIT_SUCCESS);
}
