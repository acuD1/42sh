/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/02 15:10:57 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Global variable are initialized here. We need to figure it out wich ones
**	need to be shared.
*/

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
	shell->lexer = NULL;
	shell->job_list = NULL;
	shell->assign_list = NULL;
}
