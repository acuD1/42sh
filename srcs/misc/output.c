/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:20:07 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/16 17:12:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

int		my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

void	print_n(t_read *term)
{
	if (term->ctrl_c == FALSE)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		if (term->sub_prompt == TRUE)
			display_subprompt(term);
		else
			display_prompt(term);
	}
}

void	version(t_core *shell)
{
	ft_dprintf(STDOUT_FILENO,
		"%s|%sv.%d_%d_%d%s|%s 42sh%s\n\n",
		C_G, C_X,
		shell->build.release, shell->build.version, shell->build.patch,
		C_G, C_Y, C_X);
}
