/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:07:31 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/10 18:31:06 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh42.h"

void			print_history(t_lst *saved, int i)
{
	while (saved->next)
		saved = saved->next;
	while (saved)
	{
		ft_dprintf(STDOUT_FILENO, "    %d %s\n", ++i, saved->content);
		saved = saved->prev;
	}
}

/*
**	Opt history number print n_last history data
*/

void			select_history(t_lst *history, char *cmd)
{
	int		i;
	size_t		number;

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
		ft_dprintf(STDOUT_FILENO, "    %d %s\n", i++, history->content);
		history = history->prev;
	}
}

int8_t			builtin_history(t_core *shell)
{
	t_lst		*saved;
	int		i;
	char		**cmd;

	i = -1;
	saved = shell->history;
	cmd = ft_strsplit(shell->buff, SPACE);
	/**  Just usage missing  **/
	if (cmd[1] && ft_isalpha(*cmd[1]))
	{
		ft_dprintf(STDOUT_FILENO, "42sh: history: %s: numeric argument required\n", cmd[1]);
		return (FAILURE);
	}
	else if (ft_tablen(cmd) > 2)
	{
		ft_dprintf(STDOUT_FILENO, "history: too many arguments\n");
		return (FAILURE);
	}
	else if (cmd[1] && ft_isdigit(*cmd[1]))
	{
		select_history(saved, cmd[1]);
		return (SUCCESS);
	}
	else if (saved && !cmd[1])
		print_history(saved, i);
	return (SUCCESS);
}
