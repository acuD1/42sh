/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:05:56 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/21 19:52:25 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			get_pat_and_rep(char **av, char **pat,	char **rep)
{
	char			*str;

	str = NULL;
	if (av == NULL || ft_tablen(av) == 2)
		return ;
	skip_options(&av);
	av++;
	str = ft_strdup(*av);
	*rep = ft_strchr(str, '=');
	if (*rep == NULL)
		return ;
	**rep = '\0';
	(*rep)++;
	(*pat) = str;
}

static int8_t	replace_pattern(t_core *shell, char *pat, char *rep)
{
	char		*pat_index;
	char		*replace;
	char		*tmp;

	if (pat == NULL || rep == NULL || !*pat)
		return (FAILURE);
	tmp = ft_strdup(shell->term.history->content);
	if ((pat_index = ft_strstr(tmp, pat)) == NULL)
		return (FAILURE);
	replace = ft_strsub(tmp, 0, pat_index - tmp);
	ft_strdel(&tmp);
	tmp = ft_strjoin(replace, rep);
	ft_strdel(&replace);
	replace = ft_strjoin(tmp, pat_index + ft_strlen(pat));
	shell->term.buffer = ft_strdup(replace);
	ft_strdel(&tmp);
	ft_strdel(&replace);
	ft_strdel(&pat);
	return (SUCCESS);
}

/*
**	[fc -s [old=new] [specifier]]
**		=> select specifier in history to re-enter
**		=> if new is specified history lst and file will b edit
*/

int8_t		select_specifier(t_core *shell, char **av)
{
	t_cmd	cmd;
	char	*pat;
	char	*rep;

	pat = NULL;
	rep = NULL;
	cmd.fd = STDERR_FILENO;
	if (shell->term.history == NULL)
		return (fc_error(0, 0));
	get_pat_and_rep(av, &pat, &rep);
	ft_strdel(&shell->term.buffer);
	if (pat == NULL || rep == NULL)
		shell->term.buffer = ft_strdup(shell->term.history->content);
	else
		while (replace_pattern(shell, pat, rep) == SUCCESS)
			;
	if (!shell->term.buffer)
		shell->term.buffer = ft_strdup(shell->term.history->content);
	ft_dprintf(cmd.fd, "%s\n", shell->term.buffer);
	lexer_parser_analyzer(shell);
	do_job_notification(shell, shell->launched_jobs);
	if (task_master(shell) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
