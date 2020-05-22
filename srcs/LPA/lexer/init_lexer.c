/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:21:39 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 05:51:34 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	ft_init_lex(t_lexer *lexer)
{
	lexer->lex[L_START] = start_lexer;
	lexer->lex[L_OPERATOR] = operator_lexer;
	lexer->lex[L_NAME] = name_lexer;
	lexer->lex[L_IO_NUMBER] = number_lexer;
	lexer->lex[L_NEWLINE] = newline_lexer;
	lexer->lex[L_DISCARD] = discard_lexer;
	lexer->lex[L_ASSIGNEMENT_WORD] = assignement_word_lexer;
	lexer->lex[L_END] = end_lexer;
}

void		init_lexer(char *line, t_lexer *new)
{
	if (!line)
		return ;
	new->buff = line;
	new->status = L_START;
	new->ntok = 0;
	new->buf_pos = 0;
	new->token.data = NULL;
	new->token.id = P_ERROR;
	ft_init_lex(new);
}

t_token		*fetch_token(t_token *token, enum e_pstate type, const char *data)
{
	token->id = type;
	if (!(token->data = ft_strdup(data)))
		token->data = NULL;
	if (token->data)
		token->len = ft_strlen(token->data);
	else
		token->len = 0;
	return (token);
}
