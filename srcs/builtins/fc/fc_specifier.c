/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:05:56 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/27 13:20:02 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			get_pat_and_rep(char ***av, char **pat,	char **rep)
{
	char			*str;

	str = NULL;
	if (**av == NULL)
		return ;
	while (**av && (*av)++)
	{
		if (isstart(**av, "-l") || isstart(**av, "-r")
			|| isstart(**av, "-n") || isstart(**av, "-s")
			|| isstart(**av, "-e"))
			continue ;
		else
		{
			str = ft_strdup(**av);
			break ;
		}
	}
	*rep = ft_strchr(str, '=');
	if (*rep == NULL)
		return ;
	**rep = '\0';
	(*rep)++;
	(*pat) = str;
}

/*
**	[fc -s [old=new] [specifier]]
**		=> select specifier in history to reenter
**		=> if new is specified history lst and file will b edit
*/

int8_t		select_specifier(t_core *shell, t_lst *w, char **av)
{
	char	*pat;
	char	*rep;

	pat = NULL;
	rep = NULL;
	(void)shell;
	(void)w;
	get_pat_and_rep(&av, &pat, &rep);
	printf("[%s] [%s] [%s]\n", *av, pat, rep);
	/* if (cmd[0] && !ft_strchr(cmd[0], '=')) */
	/* { */
	/* 	if (ft_atoi(cmd[0]) < 0) */
	/* 		cmd[0] = ft_itoa(ft_lstlen(w) + ft_atoi(cmd[0])); */
	/* 	while (ft_atoi(cmd[0]) != 0 && w->next) */
	/* 	{ */
	/* 		if (!ft_isdigit(*cmd[0]) && isstart((char *)w->content, cmd[0])) */
	/* 			break ; */
	/* 		else if (ft_atoi(cmd[0]) == (int)w->content_size) */
	/* 			break ; */
	/* 		w = w->next; */
	/* 	} */
	/* } */
	/* if (cmd[0] && !ft_isdigit(*cmd[0]) && !(w->next)) */
	/* 	return (FAILURE); */
	/* ft_strdel(&shell->term.buffer); */
	/* shell->term.buffer = ft_strdup(w->content); */
	/* ft_printf("%s\n", shell->term.buffer); */
	/* exec_process(shell, shell->env); */
	return (SUCCESS);
}
