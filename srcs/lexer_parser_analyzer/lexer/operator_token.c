/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:46:41 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/03 14:43:41 by arsciand         ###   ########.fr       */
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
	{P_LESSAND, "<&", 2},
	{P_LESS, "<", 1},
	{P_DGREAT, ">>", 2},
	{P_GREATAND, ">&", 2},
	{P_GREAT, ">", 1},
	{P_OPE_INTERRUPT, NULL, 0}
};

/*
** STATE CREANT LES TOKENS DE LA STRUCT OPE CI DESSUS
*/

static int	create_operator_token(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
{
	char *str;

	str = NULL;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len)))
		return (0);
	if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, id, str), sizeof(t_token)))))
		return (0);
	free(str);
	lexer->ntok++;
	lexer->buf_pos += len;
	lexer->status = L_START;
	return (1);
}

t_lst		*operator_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int 	i;

	i = 0;
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return(lexer_token);
	}
	while (ope[i].id != P_OPE_INTERRUPT)
	{
		if (!ft_strncmp(&lexer->buff[lexer->buf_pos], ope[i].data, ope[i].data_len))
		{
			if (create_operator_token(lexer, ope[i].id, ope[i].data_len, lexer_token))
				break;
		}
		i++;
	}
	if (i == NB_OF_OPE)
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return(lexer_token);
}
