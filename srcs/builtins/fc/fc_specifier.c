/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:05:56 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/30 18:57:31 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static void		get_pat_and_rep(char **av, char **pat, char **rep)
{
	char		*tmp;

	tmp = NULL;
	if (av == NULL || ft_tablen(av) == 2)
		return ;
	skip_options(&av);
	av++;
	tmp = ft_strdup(*av);
	*pat = tmp;
	if ((*rep = ft_strchr(*pat, '=')) == NULL)
		return ;
	**rep = '\0';
	(*rep)++;
}

static int8_t	replace_pattern(t_core *shell, char *pat, char *rep)
{
	char		*pat_index;
	char		*replace;
	char		*tmp;

	replace = NULL;
	pat_index = NULL;
	if (pat == NULL || rep == NULL || !*pat || !*rep)
		return (FAILURE);
	if (ft_strequ(pat, rep) == TRUE)
		return (FAILURE);
	if ((pat_index = ft_strstr(shell->term.buffer, pat)) == NULL)
		return (FAILURE);
	tmp = ft_strdup(shell->term.buffer);
	replace = ft_strsub(tmp, 0, (size_t)(pat_index - shell->term.buffer));
	ft_strdel(&tmp);
	tmp = ft_strjoinf(replace, rep, 1);
	replace = ft_strjoinf(tmp, pat_index + ft_strlen(pat), 1);
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_strdup(replace);
	ft_strdel(&replace);
	return (SUCCESS);
}

static void		replace_cmd_spe(t_core *shell, int32_t cmd)
{
	t_lst		*w;

	w = shell->term.history;
	while (w)
	{
		if (cmd == (int32_t)w->content_size)
		{
			ft_strdel(&shell->term.buffer);
			shell->term.buffer = ft_strdup(w->content);
		}
		w = w->next;
	}
}

static int8_t	select_cmd_spe(t_core *shell, char *pat)
{
	int32_t		w_entries;
	int32_t		digit;

	digit = ft_atoi(pat);
	w_entries = (int32_t)ft_lstlen(shell->term.history);
	if (digit == 0 && ft_strisdigit(pat))
		digit = 1;
	else if (digit <= 0)
	{
		if (!ft_isnum(pat))
		{
			if ((digit = check_pattern(pat)) == FAILURE)
				return (FAILURE);
		}
		else if ((digit * (-1)) > w_entries)
			digit = 1;
		else
			digit = w_entries + digit + 1;
		replace_cmd_spe(shell, digit);
	}
	else
		replace_cmd_spe(shell, digit);
	return (SUCCESS);
}

/*
**			[fc -s [old=new] [specifier]]
**		=> select specifier in history to re-enter
**		=> if new is specified history lst and file will b edit
*/

int8_t			select_specifier(t_core *shell, char **av)
{
	char		*pat;
	char		*rep;

	pat = NULL;
	rep = NULL;
	if (shell->term.history == NULL)
		return (fc_error(0, 0));
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_strdup(shell->term.history->content);
	get_pat_and_rep(av, &pat, &rep);
	if (ft_tablen(av) > 2 && rep == NULL)
	{
		if (select_cmd_spe(shell, pat) == FAILURE)
		{
			ft_strdel(&pat);
			return (fc_error(0, 3));
		}
	}
	else
		while (replace_pattern(shell, pat, rep) == SUCCESS)
			;
	ft_strdel(&pat);
	print_and_exec(shell, STDERR_FILENO);
	return (SUCCESS);
}
