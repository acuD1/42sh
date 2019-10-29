/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:04:32 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/29 17:01:48 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		reverse_range(t_lst **w, char **range)
{
	size_t	number;

	number = 0;
	if (ft_tablen(range) != 2)
		return ;
	else if (range[1] && ft_atoi(range[0]) > ft_atoi(range[1]))
		number = ft_atoi(range[0]);
	else if (range[1])
		number = ft_atoi(range[1]);
	while ((*w)->next && number != (*w)->content_size)
		*w = (*w)->next;
	if (range[1] && ft_atoi(range[0]) < ft_atoi(range[1]))
	{
		number = ft_atoi(range[1]);
		range[1] = range[0];
		range[0] = ft_itoa(number);
	}
}

void		set_range(t_lst **w, char **range)
{
	int16_t		len;

	if (range[0] && ft_atoi(range[0]) < 0)
		len = ft_atoi(range[0]) * (-1);
	else if (range[0] && ft_atoi(range[0]) > 0)
		len = ft_lstlen(*w) - ft_atoi(range[0]);
	else
		len = 17;
	if (len < 0 || (size_t)len > ft_lstlen(*w))
		len = 0;
	while ((*w)->next && --len > 0)
		*w = (*w)->next;
}

void		listing_mode(t_lst *saved, u_int64_t opt, char **range)
{
	u_int16_t	n;

	n = (range[0]) ? ft_lstlen(saved) : 17;
	if (range[0] && (opt & (1ULL << 17)))
		n = ft_lstlen(saved) - ft_atoi(range[0]);
	if (opt & (1ULL << 17))
		reverse_range(&saved, range);
	else
		set_range(&saved, range);
	while (saved && n--)
	{
		if ((opt & (1ULL << 13)))
			ft_dprintf(STDOUT_FILENO, "\t%s\n", saved->content);
		else
			ft_dprintf(STDOUT_FILENO, "%d\t%s\n", saved->content_size, saved->content);
		if (range[1] && (int)saved->content_size == ft_atoi(range[1]))
			break ;
		saved = ((opt & (1ULL << 17)) ? saved->next : saved->prev);
	}
}

/* int32_t			get_hist_size(t_core *shell, char *hist_var) */
/* { */
/* 	t_lst		*env; */
/* 	int32_t		hist_size; */
/*  */
/* 	hist_size = 0; */
/* 	env = shell->env; */
/* 	while (env) */
/* 	{ */
/* 		if (!ft_strcmp(hist_var, ((t_db*)(env->content))->key)) */
/* 		{ */
/* 			hist_size = atoi(((t_db*)(env->content))->value); */
/* 			break ; */
/* 		} */
/* 		env = env->next; */
/* 	} */
/* 	return (hist_size); */
/* } */

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

void			get_range(char **cmd, char **range)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	range[0] = NULL;
	ft_bzero(range, sizeof(range));
	ft_bzero(range[1], sizeof(range[1]));
	while (j < 2 && cmd && cmd[++i])
	{
		if (isstart(cmd[i], "-l") || isstart(cmd[i], "-r")
			|| isstart(cmd[i], "-n") || isstart(cmd[i], "-s"))
			continue ;
		else
			range[++j] = cmd[i];
	}
	range[j + 1] = 0;
	if (ft_tablen(range) == 2 && ft_atoi(range[0]) > ft_atoi(range[1]))
	{
		j = ft_atoi(range[1]);
		range[1] = range[0];
		range[0] = ft_itoa(j);
	}
}

/*
**	Fix Command builtin have 2 modes :
**		Editing (default) & Listing (-lnr options)
*/

int8_t			builtin_fc(t_core *shell)
{
	t_lst		*saved;
	char		**cmd;
	char		*range[2];
	u_int64_t	opt;

	saved = shell->history;
	cmd = ft_strsplit(shell->buff, SPACE);
	opt = get_options(ft_tablen(cmd), cmd, "elnrs0123456789");
	get_range(cmd, range);
	if (opt & (1ULL << 63))
		return (FAILURE);
	else if (saved && (opt & (1ULL << 18)))
		return (select_specifier(shell, saved, range));
	else if (saved && (opt & (1ULL << 11)))
		listing_mode(saved, opt, range);
	return (SUCCESS);
}
