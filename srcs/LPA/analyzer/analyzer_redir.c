/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:43 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/15 18:05:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_redir(t_redir *new)
{
	ft_bzero(new, sizeof(t_redir));
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
	new->heredoc = NULL;
}

t_analyzer	*heredoc_analyzer(t_analyzer *anal, t_core *shell)
{
	char	*line;

	line = NULL;
	anal->redir.op[1] = quote_backslash_discarder(((t_token*)anal->lexer->content)->data);
	if (shell->mode & I_MODE)
		anal->redir.heredoc = load_heredoc(shell, anal->redir.op[1]);
	else
	{
		while (ft_getnextline(STDIN_FILENO, &line) > 0 && ft_strcmp(line, anal->redir.op[1]) != 0)
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
	}
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*redir_wanalyze(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	// if (anal->state == A_REDIRECT)
	if (anal->redir.type == P_DLESS || anal->redir.type == P_DLESSDASH)
		return (heredoc_analyzer(anal, shell));
	else
		anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*redir_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	ft_lstappend(&anal->redir_list,
		ft_lstnew(&anal->redir, sizeof(t_redir)));
	init_redir(&anal->redir);
	return (anal);
}

t_analyzer	*redirect_analyze(t_analyzer *analyzer, t_core *shell)
{
	(void)shell;
	analyzer->job.command = fill_cmd_job(analyzer->lexer,
		analyzer->job.command);
	// if ((((t_token*)analyzer->lexer->content)->id == P_DLESS
	// 	|| ((t_token*)analyzer->lexer->content)->id == P_DLESSDASH)
	// 	&& ((t_token*)analyzer->lexer->next->content)->id == P_LESS)
	// {
	// 	// analyzer->lexer = analyzer->lexer->next;
	// 	analyzer->job.command = fill_cmd_job(analyzer->lexer,
	// 		analyzer->job.command);
	// }
	analyzer->redir.type = ((t_token*)analyzer->lexer->content)->id;
	analyzer->state = A_REDIRECT;
	return (analyzer);
}
