/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:18 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/24 18:26:45 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_analyzer	*escape_sequence_analyzer(t_analyzer *analyzer)
{
	// char	*str;

	// str = NULL;
	// str = ft_strnew(0);
	// while (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ
	// 	&& ((t_token*)analyzer->lexer->next->content)->id != P_END)
	// {
	// 	if (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ
	// 		|| ((t_token*)analyzer->lexer->content)->id == P_SEMICOLON)
	// 		get_token(analyzer);
	// 	if (((t_token*)analyzer->lexer->next->content)->id == P_END)
	// 		break ;
	// 	str = ft_strjoinf(str, ((t_token*)analyzer->lexer->content)->data, 1);
	// 	get_token(analyzer);
	// }
	// printf("{%s}\n", str);
	// ft_strdel(&(((t_token*)analyzer->lexer->content)->data));
	// ((t_token*)analyzer->lexer->content)->data = ft_strdup(str);
	// ft_strdel(&(str));
	// analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av,
		// ((t_token*)analyzer->lexer->content)->data);
	// ((t_token*)analyzer->lexer->content)->id = P_ESCSEQ;
	return (analyzer);
}

t_analyzer *heredoc_analyzer(t_analyzer *anal, t_core *shell)
{
	char *key;
	char *value;

	key = NULL;
	value = NULL;
	key = ft_strdup(((t_token*)anal->lexer->content)->data);
	if (!shell->term.history_index)
		value = load_heredoc(shell, key);
	//ft_printf("key {%s} value [%s]\n", key, value);
	ft_strdel(&value);
	ft_strdel(&key);
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*process_word_analyze(t_analyzer *anal)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->process.command = fill_cmd_job(anal->lexer, anal->process.command);
	ft_lstappend(&anal->process.tok_list, ft_lstnew(fetch_token(&anal->tok,
		((t_token*)anal->lexer->content)->id, ((t_token*)anal->lexer->content)->data), sizeof(t_token)));
	return (anal);
}

t_analyzer	*cmd_analyze(t_analyzer *anal, t_core *shell)
{
	if (anal->state == A_REDIRECT)
	{
		if (anal->redir.type == P_DLESS)
			return (heredoc_analyzer(anal, shell));
		else
			return (anal = redir_wanalyze(anal, shell));
	}
	// else if (((t_token*)anal->lexer->content)->id == P_ESCSEQ)
		// anal = escape_sequence_anal(anal);
	else
		anal = process_word_analyze(anal);
	anal->state = A_WORD;
	return (anal);
}
		// analyzer = heredoc_analyzer(analyzer, shell);