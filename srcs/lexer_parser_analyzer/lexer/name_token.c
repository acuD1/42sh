/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_io_nwln_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:23:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/03 14:56:27 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lst		*quote_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	i = lexer->buf_pos + 1;
	str = NULL;
	while (lexer->buff[i] && lexer->buff[i] != '\'')
		i++;
	i++;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
		fetch_token(&lexer->token, P_QUOTE, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst		*dbquote_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	i = lexer->buf_pos + 1;
	str = NULL;
	while (lexer->buff[i] && lexer->buff[i] != '\"')
		i++;
	i++;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
		fetch_token(&lexer->token, P_DBQUOTE, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst		*bquote_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	i = lexer->buf_pos + 1;
	str = NULL;
	while (lexer->buff[i] && lexer->buff[i] != '`')
		i++;
	i++;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
		fetch_token(&lexer->token, P_BQUOTE, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst		*word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	i = lexer->buf_pos;
	str = NULL;
	while (!ft_strchr(CHAR_INTERRUPT, lexer->buff[i]) && lexer->buff[i])
		i++;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
		fetch_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst		*name_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	if (lexer->buff == '\0')
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	if (lexer->buff[lexer->buf_pos] == '\"')
		lexer_token = dbquote_lexer(lexer, lexer_token);
	else if (lexer->buff[lexer->buf_pos] == '`')
		lexer_token = bquote_lexer(lexer, lexer_token);
	else if (lexer->buff[lexer->buf_pos] == '\'')
		lexer_token = quote_lexer(lexer, lexer_token);
	else if (ft_strchr(EXPANSION, lexer->buff[lexer->buf_pos]))
		lexer_token = expansion_lexer(lexer, lexer_token);
	else
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return (lexer_token);
}
