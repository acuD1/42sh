/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:40:06 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/20 18:33:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

void		print_history(t_history *saved, int i)
{
	while (saved->next)
		saved = saved->next;
	while (saved )
	{
		my_printf(" %d %s\n", ++i, saved->data);
		saved = saved->prev;
	}
}

void		history_selected(t_history *saved, char *cmd)
{
	int		i;
	int		number;

	i = -1;
	if (ft_isdigit(*cmd))
	{
		number = ft_atoi(cmd);
		while (saved->next)
			saved = saved->next;
		while (saved && ++i < number)
			saved = saved->prev;
		while (saved)
		{
			my_printf(" %d %s\n", i++, saved->data);
			saved = saved->prev;
		}
	}
}

int			history(t_read *line, char **cmd)
{
	t_history	*saved;
	int			i;

	i = -1;
	saved = line->history;
	if (saved && line->ac > 2)
	{
		my_printf("history: too many arguments\n");
		return (1);
	}
	else if (cmd[1])
	{
		while (cmd[1][++i])
		{
			if (ft_isdigit(cmd[1][i]))
				continue ;
			else
				return (1);
		}
		history_selected(saved, cmd[1]);
		return (1);
	}
	else if (saved)
		print_history(saved, i);
	return (1);
}
