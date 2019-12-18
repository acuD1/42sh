/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:41:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/30 17:05:08 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lst		*backslash_lexer(t_lexer *lx, t_lst *lexer_token)
{
	char *str;

	str = NULL;
	if (!lx->buff)
	{
		lx->status = L_END;
		return (lexer_token);
	}
	if (lx->buff[lx->buf_pos] == '\\')
	{
		if (!(str = ft_strsub(lx->buff, lx->buf_pos, 1)))
			return (lexer_token);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lx->token, P_ESCSEQ, str), sizeof(t_token)))))
			return (lexer_token);
		free(str);
		lx->ntok++;
		lx->buf_pos++;
	}
	lx->status = L_START;
	return (lexer_token);
}

t_lst		*start_lexer(t_lexer *lx, t_lst *lexer_token)
{
	if (lx->buff[lx->buf_pos] == '\0')
		lexer_token = end_lexer(lx, lexer_token);
	else if (lx->buff[lx->buf_pos] == ' ' || lx->buff[lx->buf_pos] == '\t')
	{
		if (lx->buff[lx->buf_pos - 1] && lx->buff[lx->buf_pos - 1] == '\\')
			ft_lstappend(&lexer_token, ft_lstnew(
				fetch_token(&lx->token, P_WORD, " "), sizeof(t_token)));
		while (lx->buff[lx->buf_pos] == ' ' || lx->buff[lx->buf_pos] == '\t')
			lx->buf_pos++;
	}
	else if (lx->buff[lx->buf_pos] == '\n')
		lx->status = L_NEWLINE;
	else if (lx->buff[lx->buf_pos] == '\\')
		lx->status = L_ESCSEQ;
	else if (ft_strchr(OPERATORS, lx->buff[lx->buf_pos]))
		lx->status = L_OPERATOR;
	else if (ft_isdigit(lx->buff[lx->buf_pos]))
		lx->status = L_IO_NUMBER;
	else if (ft_strchr(&lx->buff[lx->buf_pos], '='))
		lx->status = L_ASSIGNEMENT_WORD;
	else
		lx->status = L_NAME;
	return (lexer_token);
}

t_lst		*end_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	ft_lstappend(&lexer_token, ft_lstnew(
		fetch_token(&lexer->token, P_END, "(null)"), sizeof(t_token)));
	lexer->ntok++;
	lexer->status = L_END;
	return (lexer_token);
}

t_lst		*lexer(char *line)
{
	t_lexer	lexer;
	t_lst	**head;
	t_lst	*lexer_token;

	head = NULL;
	lexer_token = NULL;
	if (line == NULL)
		return (NULL);
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return (NULL);
	init_lexer(line, &lexer);
	head = &lexer_token;
	while (lexer.status != L_END)
		lexer_token = lexer.lex[lexer.status](&lexer, *head);
	lexer_token = *head;
	ft_printtoklist(lexer_token);
	lexer_token = *head;
	init_lexer(NULL, &lexer);
	return (*head);
}
