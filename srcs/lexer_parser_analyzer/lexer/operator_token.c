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
	{P_NEWLINE, "\n", 1},
	{P_ANDIF , "&&", 2},
	{P_AND, "&", 1},
	{P_ORIF, "||", 2},
	{P_PIPE, "|", 1},
	{P_DSEMI, ";;", 2},
	{P_SEMICOLON, ";", 1},
	{P_DLESSDASH, "<<-", 3},
	{P_DLESS, "<<", 2},
	{P_LESSGREAT, "<>", 2},
	{P_LESSAND, "<&", 2},
	{P_LESS, "<", 1},
	{P_DGREAT, ">>", 2},
	{P_GREATAND, ">&", 2},
	{P_GREAT, ">", 1},
	{P_TOKEN, NULL, 0}
};

/*
** STATE CREANT LES TOKENS DE LA STRUCT OPE CI DESSUS
*/

static int	create_operator_token(t_lexer *lexer, e_parser_state id, int len)
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
		while (ope[i].id != P_TOKEN)
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
