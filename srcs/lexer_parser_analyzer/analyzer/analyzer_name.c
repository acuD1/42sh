/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:18 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:19 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	**create_tablo(char *str)
{
	char	**tablo;

	if (!str)
		return (NULL);
	tablo = NULL;
	if (!(tablo = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	tablo[0] = ft_strdup(str);
	tablo[1] = NULL;
	return (tablo);
}

char		**ft_add_arg_cmd_process(char **tablo, char *str)
{
	char	**tb;
	int		j;

	j = 0;
	tb = NULL;
	if (!str)
		return (NULL);
	if (!tablo)
		return (tablo = create_tablo(str));
	if (!(tb = (char**)malloc(sizeof(char*) * (ft_tablen(tablo) + 2))))
		return (NULL);
	while (tablo[j])
	{
		tb[j] = ft_strdup(tablo[j]);
		free(tablo[j]);
		j++;
	}
	tb[j] = ft_strdup(str);
	tb[j + 1] = NULL;
	free(tablo);
	return (tb);
}

char		*fill_cmd_job(t_analyzer *analyzer, int flag)
{
	char	*str;

	str = NULL;
	if (((t_token*)analyzer->lexer->next->content)->id == 0 || !flag)
		str = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	else
		str = ft_strjoin(((t_token*)analyzer->lexer->content)->data, " ");
	analyzer->job.command = ft_strjoinf(analyzer->job.command, str, 4);
	return (analyzer->job.command);
}

t_analyzer	*escape_sequence_analyzer(t_analyzer *analyzer)
{
	char	*str;

	str = NULL;
	str = ft_strnew(0);
	while (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ
		&& ((t_token*)analyzer->lexer->next->content)->id != P_END)
	{
		if (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ
			|| ((t_token*)analyzer->lexer->content)->id == P_SEMICOLON)
			get_token(analyzer);
		if (((t_token*)analyzer->lexer->next->content)->id == P_END)
			break ;
		str = ft_strjoinf(str, ((t_token*)analyzer->lexer->content)->data, 1);
		analyzer->job.command = fill_cmd_job(analyzer, 1);
		get_token(analyzer);
	}
	free(((t_token*)analyzer->lexer->content)->data);
	((t_token*)analyzer->lexer->content)->data = ft_strdup(str);
	free(str);
	analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av,
		((t_token*)analyzer->lexer->content)->data);
	((t_token*)analyzer->lexer->content)->id = P_WORD;
	return (analyzer);
}

t_analyzer	*cmd_analyze(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal, 1);
	if (anal->state == A_REDIRECT)
	{
		anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
		anal->state = A_WORD;
		return (anal = redir_analyze(anal, shell));
	}
	else if (anal->state == A_ASSIGN)
		return (anal = ass_analyze(anal));
	else if (((t_token*)anal->lexer->content)->id == P_ESCSEQ)
		escape_sequence_analyzer(anal);
	else
	{
		anal->process.av = ft_add_arg_cmd_process(anal->process.av,
			((t_token*)anal->lexer->content)->data);
		if (is_expansion(((t_token*)anal->lexer->content)->id))
		{
			anal->process.type = ((t_token*)anal->lexer->content)->id;
			anal->job.type = ((t_token*)anal->lexer->content)->id;
		}
		anal->state = A_WORD;
	}
	return (anal);
}
