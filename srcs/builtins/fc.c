/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:04:32 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/24 22:25:13 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		select_history(t_lst *history, char *cmd)
{
	int	i;
	size_t	number;

	i = ft_lstlen(history);
	if ((number = ft_atoi(cmd)) > ft_lstlen(history))
		number = ft_lstlen(history);
	while (history && --number)
	{
		history = history->next;
		i--;
	}
		history = history->prev;
	while (history)
	{
		ft_dprintf(STDOUT_FILENO, " %d %s\n", i++, history->content);
		history = history->prev;
	}
}

u_int8_t	set_padding(t_lst **w, u_int64_t opt, int16_t len)
{
	u_int8_t	decade;
	int		i;

	decade = 0;
	i = ft_lstlen(*w);
	if (len < 0 || len > i)
		len = 0;
	while (!(opt & (1ULL << 17)) && (*w)->next && --len > 0)
	{
		i--;
		if (decade < ft_decade(i))
			decade = ft_decade(i);
		*w = (*w)->next;
	}
	return (decade);
}



void		listing_mode(t_lst *saved, u_int64_t opt, char **range)
{
	int16_t	len;
	u_int16_t	n;
	u_int8_t	decade;

	len = (range[0]) ? ft_lstlen(saved) - ft_atoi(range[0]) : 17;
	n = (range[0]) ? ft_lstlen(saved) : 17;
	decade = set_padding(&saved, opt, len);
	while (saved && n-- && (int)saved->content_size != ft_atoi(range[1]) + 1)
	{
		if ((opt & (1ULL << 13)))
			ft_dprintf(STDOUT_FILENO, "\t%s\n", saved->content);
		else
			ft_dprintf(STDOUT_FILENO, "%-*d\t%s\n", decade, saved->content_size, saved->content);
		saved = ((opt & (1ULL << 17)) ? saved->next : saved->prev);
		// To be continued....
		if ((opt & (1ULL << 17) && range[0] && ft_atoi(range[0]) == ((int)saved->content_size + 1)))
			break ;
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
	int	len;

	len = ft_lstlen(w);
	if (cmd[2] && !ft_strchr(cmd[2], '='))
	{
		if (ft_atoi(cmd[2]) > 0)
			len -= ft_atoi(cmd[2]);
		while (w->next && len--)
		{
			if (!ft_isdigit(*cmd[2]) && isstart((char *)w->content, cmd[2]))
				break ;
			w = w->next;
		}
	}
	if (cmd[2] && !ft_isdigit(*cmd[2]) && len == 1)
		return (FAILURE);
	ft_bzero(shell->buff, ft_strlen(shell->buff));
	shell->buff = ft_strdup(w->content);
	get_tokens(shell, shell->buff);
	ft_printf("%s\n", shell->buff);
	exec_process(shell, shell->env);
	return (SUCCESS);
}

char			**get_range(char **cmd, char **range)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	ft_bzero(range, sizeof(range));
	while (cmd && cmd[++i] && j < 2)
	{
		if (ft_strchr(cmd[i], '-'))
			continue ;
		else
			range[++j] = cmd[i];
	}
	return (range);
}

/*
**	Fix Command builtin have 2 modes :
**		Editing (default) & Listing (-l option)
*/

int8_t			builtin_fc(t_core *shell)
{
	t_lst		*saved;
	char		**cmd;
	char		*range[2];
	u_int64_t	opt;

	saved = shell->history;
	cmd = ft_strsplit(shell->buff, SPACE);
	opt = get_options(ft_tablen(cmd), cmd, "elnrs");
	get_range(cmd, range);
	if (opt & (1ULL << 63))
		return (FAILURE);
	if (saved && (opt & (1ULL << 18)))
		return (select_specifier(shell, saved, cmd));
	/* if (cmd[1] && ft_isdigit(*cmd[1])) */
	/* { */
	/* 	select_history(saved, cmd[1]); */
	/* 	return (SUCCESS); */
	/* } */
	else if (saved && (opt & (1ULL << 11)))
		listing_mode(saved, opt, range);
	return (SUCCESS);
}
