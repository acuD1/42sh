/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:13:54 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/12 15:51:01 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char				*heredoc_inhib(char *data)
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
	shell->heredoc = 1;
	return (anal);
}

t_analyzer			*heredoc_analyzer(t_analyzer *anal, t_core *shell)
{
	anal->redir.op[1] = heredoc_inhib(((t_token*)anal->lexer->content)->data);
	if (shell->is_interactive)
		anal->redir.heredoc = load_heredoc(shell, anal->redir.op[1]);
	else
		anal = load_heredoc_noimode(anal, shell);
	if (!shell->heredoc)
		return (exit_lpa(anal, shell));
	anal->state = A_WORD;
	shell->term.flag = FALSE;
	shell->term.status = CMD_DONE;
	return (anal = redir_analyze(anal, shell));
}
