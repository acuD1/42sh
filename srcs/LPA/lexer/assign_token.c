/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:45:53 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/12 17:11:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static size_t	isvalid_assignement_word(const char *str, size_t index)
{
	size_t	i;

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
	if (str[i + 1] && (str[i + 1] == '='))
		return (0);
	return (i + 1);
}

static t_lst	*create_assign_token
	(t_lexer *lex, size_t len, t_lst *lexer_token)
{
	char	*str;
	size_t	value_len;

	str = NULL;
	value_len = 0;
	value_len = get_word_size_ntype(len, lex->buff);
	if (!value_len)
		value_len = len;
	if (!(str = ft_strsub(lex->buff, (unsigned int)lex->buf_pos,
		value_len - lex->buf_pos)))
		return (NULL);
	if (!(ft_lstappend(&lexer_token,
		ft_lstnew(fetch_token(&lex->token, P_ASSIGN, str), sizeof(t_token)))))
		return (NULL);
	ft_strdel(&str);
	lex->ntok++;
	lex->buf_pos = value_len;
	return (lexer_token);
}

t_lst			*assignement_word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	size_t	i;

	i = 0;
	if (!lexer->buff)
		lexer->status = L_END;
	else
	{
		if ((i = isvalid_assignement_word(lexer->buff, lexer->buf_pos)))
			lexer_token = create_assign_token(lexer, i, lexer_token);
		else
			lexer_token = name_lexer(lexer, lexer_token);
	}
	lexer->status = L_START;
	return (lexer_token);
}

static t_lst	*word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	size_t	i;
	char	*str;

	i = lexer->buf_pos;
	str = NULL;
	if (!(i = get_word_size_ntype(i, lexer->buff)))
		return (NULL);
	if (!(str = ft_strsub(lexer->buff,
					(unsigned int)lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
				fetch_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	ft_strdel(&str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst			*name_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	char	*str;

	str = NULL;
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return (lexer_token);
}
