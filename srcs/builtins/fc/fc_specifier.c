/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:05:56 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 16:50:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static void		get_pat_and_rep(char **av, char **pat, char **rep)
{
	char		*str;

	str = NULL;
	if (av == NULL || ft_tablen(av) == 2)
		return ;
	skip_options(&av);
	av++;
	str = ft_strdup(*av);
	(*pat) = str;
	if ((*rep = ft_strchr(str, '=')) == NULL)
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

static void		select_cmd_spe(t_core *shell, int32_t cmd)
{
	int32_t		w_entries;

	w_entries = (int32_t)ft_lstlen(shell->term.history);
	if (cmd < 0)
	{
		if ((cmd * (-1)) > w_entries)
			cmd = 1;
		else
			cmd = w_entries + cmd;
		replace_cmd_spe(shell, cmd);
	}
	else if (cmd == 0)
		cmd = 1;
	else
		replace_cmd_spe(shell, cmd);
}

/*
**			[fc -s [old=new] [specifier]]
**		=> select specifier in history to re-enter
**		=> if new is specified history lst and file will b edit
*/

int8_t			select_specifier(t_core *shell, char **av)
{
	t_cmd		cmd;
	char		*pat;
	char		*rep;

	pat = NULL;
	rep = NULL;
	cmd.fd = STDERR_FILENO;
	if (shell->term.history == NULL)
		return (fc_error(0, 0));
	get_pat_and_rep(av, &pat, &rep);
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_strdup(shell->term.history->content);
	if (ft_tablen(av) > 2 && ft_isdigit(*pat) && rep == NULL)
		select_cmd_spe(shell, ft_atoi(pat));
	else
		while (replace_pattern(shell, pat, rep) == SUCCESS)
			;
	ft_strdel(&pat);
	ft_dprintf(cmd.fd, "%s\n", shell->term.buffer);
	lexer_parser_analyzer(shell);
	do_job_notification(shell, shell->launched_jobs, TRUE);
	task_master(shell);
	return (SUCCESS);
}
