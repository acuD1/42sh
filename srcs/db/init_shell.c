/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/15 11:11:22 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Global variable are initialized here. We need to figure it out wich ones
**	need to be shared.
*/

int8_t	init_shell(t_core *shell, char **av, char **environ)
{
	if (set_env(shell, av, environ) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: Cannot allocate memory\n");
		return (EXIT_FAILURE);
	}
	shell->build.release = BUILDR;
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->hash.size = HASH_SIZE;
	shell->heredoc = 0;
	return (SUCCESS);
}
