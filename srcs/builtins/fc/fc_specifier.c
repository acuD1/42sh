/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:05:56 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/05 19:06:20 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	[fc -s [old=new] [specifier]]
**		=> select specifier in history to reenter
**		=> if new is specified history lst and file will b edit
*/

u_int8_t	select_specifier(t_core *shell, t_lst *w, char **cmd)
{
	if (cmd[0] && !ft_strchr(cmd[0], '='))
	{
		if (ft_atoi(cmd[0]) < 0)
			cmd[0] = ft_itoa(ft_lstlen(w) + ft_atoi(cmd[0]));
		while (ft_atoi(cmd[0]) != 0 && w->next)
		{
			if (!ft_isdigit(*cmd[0]) && isstart((char *)w->content, cmd[0]))
				break ;
			else if (ft_atoi(cmd[0]) == (int)w->content_size)
				break ;
			w = w->next;
		}
	}
	if (cmd[0] && !ft_isdigit(*cmd[0]) && !(w->next))
		return (FAILURE);
	ft_bzero(shell->buff, ft_strlen(shell->buff));
	shell->buff = ft_strdup(w->content);
	get_tokens(shell, shell->buff);
	ft_printf("%s\n", shell->buff);
	exec_process(shell, shell->env);
	return (SUCCESS);
}
