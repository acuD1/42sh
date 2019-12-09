/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_nbr_nwl_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:55:48 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 17:55:53 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lst		*isvalid_ionumber(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	str = NULL;
	i = lexer->buf_pos;
	if (!lexer->buff[i] || !ft_isdigit(lexer->buff[i]))
		return (NULL);
	while (ft_isdigit(lexer->buff[i]) && lexer->buff[i])
		i++;
	if ((lexer->buff[i] == '<' || lexer->buff[i] == '>'))
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lexer->token, P_IONUMBER, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->buf_pos = i;
		lexer->ntok++;
	}
	else
		return (NULL);
	return (lexer_token);
}

t_lst		*number_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	if ((lexer_token = isvalid_ionumber(lexer, lexer_token)))
		lexer_token = operator_lexer(lexer, lexer_token);
	else
		lexer_token = name_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return (lexer_token);
}

t_lst		*newline_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	char	*str;

	str = NULL;
	if (!lexer->buff[lexer->buf_pos])
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	if (lexer->buff[lexer->buf_pos] == '\n')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, 1)))
			return (lexer_token);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lexer->token, P_NEWLINE, str), sizeof(t_token)))))
			return (lexer_token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos++;
	}
	lexer->status = L_START;
	return (lexer_token);
}
