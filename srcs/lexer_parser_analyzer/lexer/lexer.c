/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:41:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/07/31 15:43:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** ETAT DE LA STATE MACHINE DE DEFAULT ET DE DEPART
** CHANGE LE STATUS DE LA MACHINE EN FONCTION DU CHAR IDENTIFIÉ
*/

void		start_lexer(t_lexer *lexer)
{
	if (lexer->buff[lexer->buf_pos] == '\0')
	{
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, P_NEWLINE, "\n"), sizeof(t_token)))))
			return;
		init_token(&lexer->token);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, P_END, "(null)"), sizeof(t_token)))))
			return;
		init_token(&lexer->token);
		lexer->ntok++;
		lexer->status = END;
	}
	else if (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
	{
		while (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
			lexer->buf_pos++;
	}
	else if (ft_strchr(OPERATORS, lexer->buff[lexer->buf_pos]))
		lexer->status = OPERATOR;
	else if (ft_isdigit(lexer->buff[lexer->buf_pos]))
		lexer->status = IO_NUMBER;
	else if (!ft_strcmp(&lexer->buff[lexer->buf_pos], "\n"))
		lexer->status = NEWLINE;
	else if (ft_strchr(&lexer->buff[lexer->buf_pos], '='))
		lexer->status = ASSIGNEMENT_WORD;
	else
		lexer->status = NAME;
}

/*
** ETAT DE TRANSITION VERS LE PARSER ?
*/

void		end_lexer(t_lexer *lexer)
{
	lexer->status = END;
}

/*
*** LEXER IN = LINE EDITION    OUT = PARSER
*/

t_lst *lexer(char *line)
{
	t_lexer	*lexer;
	t_lst **head;

	head = NULL;
	if (line == NULL)
		return (NULL);
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return (NULL);
	lexer = init_lexer(line);
	head = &lexer->tok;
	while (lexer->status != END)
		lexer->lex[lexer->status](lexer);
	lexer->tok = *head;
	// ft_printtoklist(lexer);
	// free(lexer);
	return (*head);
}
