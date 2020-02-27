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

char		*quote_backslash_discarder(char *data)
{
	char			*res;
	char			*tmp;
	int				index;
	enum e_estate	st;

	st = NB_EXPANSION_STATE;
	if (!data)
		return (NULL);
	tmp = NULL;
	res = NULL;
	index = 0;
	while (data[index])
	{
		if (st != E_QUOTE)
			discard_backslash(data, &index, &res);
		st = skip_recur_quote(data, &index, st);
		if (!data[index])
			break ;
		if (res)
		{
			tmp = ft_strsub(data, index, 1);
			res = ft_strjoinf(res, tmp, 4);
		}
		else
			res = ft_strsub(data, index, 1);
		index++;
	}
	return (res);
}

void			free_koulchi(t_analyzer *anal)
{
	if (anal->redir.op[0])
		ft_strdel(&anal->redir.op[0]);
	if (anal->redir.op[1])
		ft_strdel(&anal->redir.op[1]);
	if (anal->redir.heredoc)
		ft_strdel(&anal->redir.heredoc);
	if (anal->redir_list)
		ft_free_redirlist(&anal->redir_list);
	if (anal->db.key)
		ft_strdel(&anal->db.key);
	if (anal->db.value)
		ft_strdel(&anal->db.value);
	if (anal->process.redir_list)
		ft_free_redirlist(&anal->process.redir_list);
	if (anal->process.assign_list)
		free_db(anal->process.assign_list);
	if (anal->process.command)
		ft_strdel(&anal->process.command);
	if (anal->process.tok_list)
		ft_freetokenlist(&anal->process.tok_list);
	if (anal->process_list)
		free_process_list(&anal->process_list);
}

t_analyzer		*exit_lpa(t_analyzer *anal)
{
	free_koulchi(anal);
	if (anal->job.command)
		ft_strdel(&anal->job.command);
	if (anal->job.process_list)
		free_process_list(&anal->job.process_list);
	if (anal->job_list)
		ft_freejoblist(&anal->job_list);
	anal->state = A_STOP;
	anal->job_list = NULL;
	return (anal);
}

void		init_redir(t_redir *new)
{
	ft_bzero(new, sizeof(t_redir));
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
	new->heredoc = NULL;
}

t_analyzer	*load_heredoc_noimode(t_analyzer *anal, t_core *shell)
{
	char	*line;

	line = NULL;
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
	shell->heredoc = 1;
	return (anal);
}

t_analyzer	*heredoc_analyzer(t_analyzer *anal, t_core *shell)
{
	anal->redir.op[1] = quote_backslash_discarder(((t_token*)anal->lexer->content)->data);
	if (shell->mode & I_MODE)
		anal->redir.heredoc = load_heredoc(shell, anal->redir.op[1]);
	else
		anal = load_heredoc_noimode(anal, shell);
	if (!shell->heredoc)
		return (exit_lpa(anal));
	anal->state = A_WORD;
	shell->term.flag = FALSE;
	shell->term.status = CMD_DONE;
	shell->heredoc = 0;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*redir_wanalyze(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
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

t_analyzer	*load_heredoc_fromline(t_analyzer *anal, t_core *shell)
{
	anal->redir.type = ((t_token*)anal->lexer->content)->id;
	anal->lexer = anal->lexer->next;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->lexer = anal->lexer->next;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	// anal->redir.op[1] = quote_backslash_discarder(((t_token*)anal->lexer->content)->data);
	anal->redir.heredoc = ft_strjoin(anal->redir.op[1], "\n");
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*redirect_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	if ((((t_token*)anal->lexer->content)->id == P_DLESS && anal->lexer->next
		&& ((t_token*)anal->lexer->next->content)->id == P_LESS))
		return (anal = load_heredoc_fromline(anal, shell));
	anal->redir.type = ((t_token*)anal->lexer->content)->id;
	anal->state = A_REDIRECT;
	return (anal);
}
