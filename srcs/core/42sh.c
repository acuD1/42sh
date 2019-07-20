/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/20 17:38:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

/*
**	TO_DO :
**	- signal
**	- logger ?
**	- A fonction for return value (exit_handler) Need talks about it..
*/

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	init_shell(&shell, environ);

	/* Parse char **av and fill option */
	if (get_opt(ac, av, &shell) != SUCCESS)
		return (EXIT_FAILURE);

	/* Get t_lst *env, a linked list of char **environ with {key}
	** and {value} format. WARNING empty char **environ not supported yet*/
	if (set_env(&shell, environ) != SUCCESS)
		return (EXIT_FAILURE);

	/* Options output */
	print_opt(&shell);

	/* Everything else will happen here */

	return (EXIT_SUCCESS);
}
