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
		if (!(ft_add_token(&lexer->tok, TOKEN, "(null)")))
			return;
		lexer->ntok++;
		lexer->status = END;
	}
	else if (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
	{
		lexer->io_here = 0;
		while (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
			lexer->buf_pos++;
	}
	else if (ft_strchr(OPERATORS, lexer->buff[lexer->buf_pos]))
		lexer->status = OPERATOR;
	else if (ft_isdigit(lexer->buff[lexer->buf_pos]))
		lexer->status = IO_NUMBER;
	else if (ft_strchr(&lexer->buff[lexer->buf_pos], '\n'))
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
	printf("USELESSSSS %u\n", lexer->status);
	// fct de liaison vers le parser ?
	// if (lexer->buff == '\0')
	// 	lexer->status = END;
	// else
	// {
	// 	lexer->status = START;
	// 	lexer->buf_pos++;
	// }
}

/*
*** LEXER IN = LINE EDITION    OUT = PARSER
*/

void		lexer(t_core *shell, char *line)
{
	t_lexer	*lexer;
	t_lexer **head;

	head = &lexer;
	if (line == NULL)
		return ;
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return ;
	lexer = init_lexer(shell, line);
	while (lexer->status != END)
		lexer->lex[lexer->status](lexer);
	// ft_printtoklist(lexer);
	parser(shell, lexer);
}
