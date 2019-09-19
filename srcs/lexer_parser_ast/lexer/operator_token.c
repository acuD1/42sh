/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:46:41 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/19 11:46:45 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static const t_token    ope[] =
{
	{TOK_NEWLINE, "\n", 1},
	{TOK_ANDIF , "&&", 2},
	{TOK_AND, "&", 1},
	{TOK_ORIF, "||", 2},
	{TOK_PIPE, "|", 1},
	{TOK_DSEMI, ";;", 2},
	{TOK_SEMICOLON, ";", 1},
	{TOK_DLESSDASH, "<<-", 3},
	{TOK_DLESS, "<<", 2},
	{TOK_LESSGREAT, "<>", 2},
	{TOK_LESSAND, "<&", 2},
	{TOK_LESS, "<", 1},
	{TOK_DGREAT, ">>", 2},
	{TOK_GREATAND, ">&", 2},
	{TOK_CLOBBER, ">|", 2},
	{TOK_GREAT, ">", 1},
	{TOKEN, NULL, 0}
};

/*
** STATE CREANT LES TOKENS DE LA STRUCT OPE CI DESSUS
*/

static int	create_operator_token(t_lexer *lexer, enum tokenid id, int len)
{
	char 	*buf;

	buf =  NULL;
	if (!(buf = ft_strsub(lexer->buff, lexer->buf_pos, len)))
		return (0);
	if (!(ft_add_token(&lexer->tok, id, buf)))
		return (0);
	// ft_lstappend(&lexer->tok, ft_lstnew(lexer_token_set(&lexer->token, id, buf), sizeof(t_token)));
	lexer->ntok++;
	lexer->buf_pos += len;
	lexer->status = START;
	free(buf);
	return (1);
}

void		operator_lexer(t_lexer *lexer)
{
	int 	i;

	i = 0;
	if (!lexer->buff)
		lexer->status = END;
	else
	{
		while (ope[i].id != TOKEN)
		{
			if (!strncmp(&lexer->buff[lexer->buf_pos], ope[i].data, ope[i].data_len))
			{
				if (create_operator_token(lexer, ope[i].id, ope[i].data_len))
					break;
			}
			i++;
		}
		if (i == NB_OF_OPE)
			name_lexer(lexer);
	}
	lexer->status = START;
}
