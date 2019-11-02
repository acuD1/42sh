/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:21:39 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:22:02 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		ft_init_lex(t_lexer *lexer)
{
	lexer->lex[L_START] = start_lexer;
	lexer->lex[L_OPERATOR] = operator_lexer;
	lexer->lex[L_NAME] = name_lexer;
	lexer->lex[L_IO_NUMBER] = number_lexer;
	lexer->lex[L_NEWLINE] = newline_lexer;
	lexer->lex[L_ASSIGNEMENT_WORD] = assignement_word_lexer;
	lexer->lex[L_EXPANSION] = expansion_lexer;
	lexer->lex[L_END] = end_lexer;
}

/*
** CELLE DU HAUT INIT LE *FCT CELLE DU BAS
** C MARKÉ DECU
*/

void init_lexer(char *line, t_lexer *new)
{
	if (!line)
		return ;
	new->buff = line; //FREE LINE et dup le buff
	new->status = L_START;
	new->ntok = 0;
	new->buf_pos = 0;
	new->token.data = NULL;
	new->token.id = P_ERROR;
	ft_init_lex(new);
	// ft_init_machine(new->machina);
}

t_token			*fetch_lexer_token(t_token *token, e_parser_state type, char *data)
{
	t_token *new;

	new = token;
	new->id = type;
	if (!(new->data = ft_strdup(data)))
		new->data = NULL;
	if (new->data)
		new->data_len = ft_strlen(new->data);
	else
		new->data_len = 0;
	return (new);
}
