/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:45:53 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/03 14:43:39 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		isvalid_assignement_word(char *str, size_t index)
{
	int			i;

	i = index;
	if (!str || ft_isdigit(str[i]) || str[i] == '=')
		return (0);
	while (str[i] != '=')
	{
		if (str[i] == '_' || ft_isdigit(str[i]) || ft_isalpha(str[i]))
			i++;
		else
			return (0);
	}
	if (str[i + 1] && str[i + 1] == '=')
		return (0);
	return (i + 1);
}

static int		get_assign_word_size(t_lexer *lex, int len)
{
	if (!lex || !lex->buff || !len)
		return (lex->buf_pos);
	while (lex->buff[len])
	{
		if (lex->buff[len] == '_' || ft_isdigit(lex->buff[len]) || ft_isalpha(lex->buff[len]))
			len++;
		else
			break;
	}
	return (len);
}

t_lst			*create_assign_token(t_lexer *lex, int len, t_lst *lexer_token)
{
	char		*str;

	str = NULL;
	len = get_assign_word_size(lex, len);
	if (!(str = ft_strsub(lex->buff, lex->buf_pos, len - lex->buf_pos)))
		return (NULL);
	if (!(ft_lstappend(&lexer_token,
		ft_lstnew(fetch_token(&lex->token, P_ASSIGN, str), sizeof(t_token)))))
		return (NULL);
	free(str);
	lex->ntok++;
	lex->buf_pos = len;
	return (lexer_token);
}

t_lst			*assignement_word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int			i;

	i = 0;
	if (!lexer->buff)
		lexer->status = L_END;
	else
	{
		if ((i = isvalid_assignement_word(lexer->buff, lexer->buf_pos)))
		{
			printf("IIIII   %d\n", i);
			lexer_token = create_assign_token(lexer, i, lexer_token);
		}
		else
			lexer_token = name_lexer(lexer, lexer_token);
	}
	lexer->status = L_START;
	return (lexer_token);
}
