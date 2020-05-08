/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:13:54 by guvillat          #+#    #+#             */
/*   Updated: 2020/05/08 00:23:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

static char			*heredoc_inhib(char *data)
{
	char			*res;
	size_t			index;
	enum e_estate	st;

	st = NB_EXPANSION_STATE;
	if (!data)
		return (NULL);
	res = NULL;
	index = 0;
	while (data[index])
	{
		if (st != E_QUOTE)
			discard_backslash(data, &index, &res);
		st = skip_recur_quote(data, &index, st);
		if (!data[index])
			break ;
		res = join_one_char(res, data, index);
		index++;
	}
	return (res);
}

t_analyzer			*load_heredoc_fromline(t_analyzer *anal, t_core *shell)
{
	anal->redir.type = ((t_token*)anal->lexer->content)->id;
	anal->lexer = anal->lexer->next;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->lexer = anal->lexer->next;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	anal->redir.heredoc = ft_strjoin(anal->redir.op[1], "\n");
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

static t_analyzer	*load_heredoc_noimode(t_analyzer *anal, t_core *shell)
{
	char	*line;

	line = NULL;
	while (ft_getnextline(STDIN_FILENO, &line) > 0
		&& ft_strcmp(line, anal->redir.op[1]) != 0)
	{
		if (!anal->redir.heredoc)
		{
			anal->redir.heredoc = ft_strdup(line);
			ft_strdel(&line);
		}
		else
			anal->redir.heredoc = ft_strjoinf(anal->redir.heredoc, line, 4);
		anal->redir.heredoc = ft_strjoinf(anal->redir.heredoc, "\n", 1);
	}
	ft_strdel(&line);
	shell->heredoc = 0;
	return (anal);
}

t_analyzer			*heredoc_analyzer(t_analyzer *anal, t_core *shell)
{
	anal->redir.op[1] = heredoc_inhib(((t_token*)anal->lexer->content)->data);
	if (shell->is_interactive)
	{
		shell->term.sub_prompt = TRUE;
		anal->redir.heredoc = load_heredoc(shell, anal->redir.op[1]);
		shell->term.sub_prompt = FALSE;
	}
	else
		anal = load_heredoc_noimode(anal, shell);
	if (shell->ctrl_c)
		return (exit_lpa(anal, shell));
	anal->state = A_WORD;
	shell->term.status = CMD_DONE;
	return (anal = redir_analyze(anal, shell));
}
