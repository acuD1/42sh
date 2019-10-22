/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:04:32 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/22 18:42:03 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh42.h"

void		listing_mode(t_lst *saved, u_int64_t opt)
{
	int	i;
	int	decade;
	int	n;

	decade = 0;
	n = 0;
	i = ft_lstlen(saved);
	while (!(opt & (1ULL << 17)) && saved->next && n++ < 15)
	{
		i--;
		if (decade < ft_decade(i))
			decade = ft_decade(i);
		saved = saved->next;
	}
	n = 15;
	i = ft_lstlen(saved);
	while (saved && n--)
	{
		(opt & (1ULL << 17)) ? i-- : i++;
		if ((opt & (1ULL << 13)))
			ft_dprintf(STDOUT_FILENO, "\t%s\n", saved->content);
		else
			ft_dprintf(STDOUT_FILENO, "%-*d\t%s\n", decade, i, saved->content);
		saved = ((opt & (1ULL << 17)) ? saved->next : saved->prev);
	}
}

/*
**	Opt history number print n_last history data
*/

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
/*  */
/* int8_t			history_errors(char **cmd) */
/* { */
/* 	if (cmd[1] && isstart(cmd[1], "-")) */
/* 	{ */
/* 		print_usage("history", cmd[1][1], "history [n]"); */
/* 		return (FAILURE); */
/* 	} */
/* 	if (cmd[1] && !ft_isdigit(*cmd[1])) */
/* 	{ */
/* 		ft_dprintf(STDOUT_FILENO, "42sh: history: %s: numeric argument required\n", cmd[1]); */
/* 		return (FAILURE); */
/* 	} */
/* 	else if (ft_tablen(cmd) > 2) */
/* 	{ */
/* 		ft_dprintf(STDOUT_FILENO, "42sh: history: too many arguments\n"); */
/* 		return (FAILURE); */
/* 	} */
/* 	return (SUCCESS); */
/* } */

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
**	Fix Command builtin have 2 modes :
**		Editing (default) & Listing (-l option)
*/

int8_t			builtin_fc(t_core *shell)
{
	t_lst		*saved;
	char		**cmd;
	u_int64_t	opt;

	saved = shell->history;
	cmd = ft_strsplit(shell->buff, SPACE);
	opt = get_options(ft_tablen(cmd), cmd, "elnrs");
	/* if (history_errors(cmd) == FAILURE) */
	/* 	return (FAILURE); */
	if (cmd[1] && ft_isdigit(*cmd[1]))
	{
		select_history(saved, cmd[1]);
		return (SUCCESS);
	}
	else if (saved && (opt & (1ULL << 11)))
		listing_mode(saved, opt);
	return (SUCCESS);
}
