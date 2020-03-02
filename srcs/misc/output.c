/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:20:07 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/15 11:01:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	version(t_core *shell)
{
	ft_dprintf(STDOUT_FILENO,
		"%s|%sv.%d_%d_%d%s|%s 42sh%s\n\n",
		C_G, C_X,
		shell->build.release, shell->build.version, shell->build.patch,
		C_G, C_Y, C_X);
}
