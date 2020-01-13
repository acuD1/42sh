/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:20:07 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/11 16:01:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	version(t_core *shell)
{
	dprintf(STDOUT_FILENO,
		"%s|%sv.%d_%d_%d%s|%s 42sh%s\n\n",
		C_G, C_X,
		shell->build.release, shell->build.version, shell->build.patch,
		C_G, C_Y, C_X);
}

void	print_opt(t_core *shell)
{
	if (shell->opt & OPT_HELP)
	{
		dprintf(STDOUT_FILENO, "42sh by %sType ./42sh\n", CREDIT);
		exit(1);
	}
	if (shell->opt & OPT_VERS)
	{
		dprintf(STDOUT_FILENO, "42sh v.%d_%d_%d_%d\n",
			shell->build.release, shell->build.version,
			shell->build.patch, shell->build.date);
		exit(1);
	}
}
