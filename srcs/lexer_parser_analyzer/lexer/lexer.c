/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:41:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/16 13:58:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** ETAT DE LA STATE MACHINE DE DEFAULT ET DE DEPART
** CHANGE LE STATUS DE LA MACHINE EN FONCTION DU CHAR IDENTIFIÉ
*/

t_lst		*start_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	if (lexer->buff[lexer->buf_pos] == '\0')
	{
		ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_NEWLINE, "\n"), sizeof(t_token)));
		ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_END, "(null)"), sizeof(t_token)));
		lexer->ntok++;
		lexer->status = L_END;
	}
	else if (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
	{
		while (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
			lexer->buf_pos++;
	}
	else if (ft_strchr(OPERATORS, lexer->buff[lexer->buf_pos]))
		lexer->status = L_OPERATOR;
	else if (ft_isdigit(lexer->buff[lexer->buf_pos]))
		lexer->status = L_IO_NUMBER;
	else if (!ft_strcmp(&lexer->buff[lexer->buf_pos], "\n"))
		lexer->status = L_NEWLINE;
	else if (ft_strchr(&lexer->buff[lexer->buf_pos], '='))
		lexer->status = L_ASSIGNEMENT_WORD;
	else
		lexer->status = L_NAME;
	return(lexer_token);
}

/*
** ETAT DE TRANSITION VERS LE PARSER ?
*/

t_lst		*end_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	lexer->status = L_END;
	return(lexer_token);
}

/*
*** LEXER IN = LINE EDITION    OUT = PARSER
*/

t_lst *lexer(char *line)
{
	t_lexer	lexer;
	t_lst **head;
	t_lst *lexer_token;

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
	//ft_printtoklist(lexer_token);
	init_lexer(NULL, &lexer);
	return (*head);
}
