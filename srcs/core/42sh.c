/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/03 15:55:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <signal.h>

/*
**	TO_DO :
**	- signal
**	- logger ?
**	- A fonction for return value (exit_handler) Need talks about it..
*/

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	init_shell(&shell);

	//shell.new_t = ft_memalloc(sizeof(shell.new_t));

	/* Parse char **av and fill option */
	if (get_opt(ac, av, &shell) != SUCCESS)
		return (EXIT_FAILURE);

	/*
	**	Get t_lst *env, a linked list of char **environ with {key}
	**	and {value} format. WARNING empty char **environ not supported yet
	*/

	// get_size AVOIDING COND JUMP ON UNINITIALIZED VALUES

	if (get_size(&(shell.cmd_line)) != SUCCESS
				|| set_env(&shell, av, environ) != SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	/* Options output */
	print_opt(&shell);

	/* Saving t_core struct */
	get_core(&shell);
	init_signals();
	/* DEBUG */
	//print_env(&shell);

	/* Everything else will happen here */

	// Need "-c implementation and a while to read everything"
	//char BUFF[16];
	if (isatty(STDIN_FILENO) == TRUE)
		load_prompt(&shell);
	else
	{
		while (ft_getnextline(STDIN_FILENO, &shell.buff))
			load_noi_mode(&shell);
		ft_strdel(&shell.buff);
	}
	/* FREE */
	free_env(shell.env);
	//free_env(shell.pos_vars);
	free_hash_map(&shell.hash);			// For now here ..

	return (EXIT_SUCCESS);
}
