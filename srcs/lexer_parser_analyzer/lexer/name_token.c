/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:15:08 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/14 16:15:10 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int 	get_word_size_ntype(int i, char *str, e_pstate *state)
{
	int index;
	e_pstate stat;

	if (!str || !str[i])
		return (0);
	index = i;
	stat = *state;
	while (str[index] && (!ft_strchr(CHAR_INTERRUPT, str[index])))// && !ft_strchr(EXPANSION, str[index])))
	{
		if (str[index] == '\'')
			while (str[index++] && str[index] != '\'')
				stat = P_QUOTE;
		if (str[index] == '`')
			while (str[index++] && str[index] != '`')
				stat = P_BQUOTE;
		if (str[index] == '\"')
			while (str[index++] && str[index] != '\"')
				stat = P_DBQUOTE;
		index++;
	}
	*state = stat;
	return (index);
}

t_lst		*word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;
	e_pstate state;

	i = lexer->buf_pos;
	str = NULL;
	state = P_WORD;
	if (!(i = get_word_size_ntype(i, lexer->buff, &state)))
		return (NULL);
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
				fetch_token(&lexer->token, state, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst	*expansion_lexer(t_lexer *lx, t_lst *lexer_token)
{
	e_pstate		state;
	char *str;

	state = P_EXP_INTERRUPT;
	str = NULL;
	if (!lx->buff)
	{
		lx->status = L_END;
		return (lexer_token);
	}
	if ((state = find_expansion(&lx->buff[lx->buf_pos])) != P_EXP_INTERRUPT)
	{
		str = get_expansion(&lx->buff[lx->buf_pos], state);
		ft_lstappend(&lexer_token, ft_lstnew(
					fetch_token(&lx->token, state, str), sizeof(t_token)));
		lx->ntok++;
		lx->buf_pos += ft_strlen(str);
		ft_strdel(&str);
		return (lexer_token);
	}
	lx->status = L_START;
	return (lexer_token = word_lexer(lx, lexer_token));
}

t_lst		*name_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	char *str;

	str = NULL;
	if (lexer->buff == '\0')
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	if (ft_strchr(EXPANSION, lexer->buff[lexer->buf_pos]))
		lexer_token = expansion_lexer(lexer, lexer_token);
	else
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return (lexer_token);
}
