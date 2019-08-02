/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/02 14:23:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Global variable are initialized here. We need to figure it out wich ones
**	need to be shared.
*/

void				init_config(void)
{
	struct termios		new_t;

	tgetent(NULL, "xterm-256color");
	if (tcgetattr(STDIN_FILENO, &old_t) == -1)
		return ;
	new_t = old_t;
	new_t.c_lflag &= ~(ICANON | ECHO);
	new_t.c_cc[VMIN] = 1;
	new_t.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_t) == -1)
		return ;
}

void	init_shell(t_core *shell)
{
	shell->build.release = BUILDR;
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->env = NULL;
	shell->tokens = NULL;
	shell->bin = NULL;
	shell->opt = 0;
	shell->buf = NULL;
}
