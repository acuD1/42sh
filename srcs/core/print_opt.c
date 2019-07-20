/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:20:07 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/20 17:34:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_opt(t_core *shell)
{
	if (shell->opt & OPT_HELP)
	{
		/* Need more stuff ... */
		ft_putendl_fd("42sh by arsciand, fcatusse and guvillat\nto run : ./42sh",
			STDOUT_FILENO);
		exit(1);
	}
	if (shell->opt & OPT_VERS)
	{
		dprintf(STDOUT_FILENO, "42sh v.%d_%d_%d_%d\n", /* /!\ */
			shell->build.release, shell->build.version,
			shell->build.patch, shell->build.date);
		exit(1);
	}
}
