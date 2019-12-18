/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:36:49 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 17:36:52 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lst		*exp_paren_lexer(t_lexer *lx, e_pstate id, int len, t_lst *lst)
{
	char	*str;
	int		index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(&lx->buff[lx->buf_pos], "$(", len))
	{
		index = lx->buf_pos;
		while (&lx->buff[index])
		{
			if (lx->buff[index] == ')')
				break ;
			index++;
		}
		index++;
		if (!(str = ft_strsub(lx->buff, lx->buf_pos, index - lx->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lst, ft_lstnew(
			fetch_token(&lx->token, id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lx->ntok++;
		lx->buf_pos = index;
	}
	return (lst);
}

t_lst		*exp_bracket_lexer(t_lexer *lx, e_pstate id, int len, t_lst *lst)
{
	char	*str;
	int		index;

	index = 0;
	str = NULL;
	if (!ft_strncmp(&lx->buff[lx->buf_pos], "${", len))
	{
		index = lx->buf_pos + 2;
		while (&lx->buff[index] && lx->buff[index] != '}')
			index++;
		index++;
		if (!(str = ft_strsub(lx->buff, lx->buf_pos, index - lx->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lst, ft_lstnew(
			fetch_token(&lx->token, id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lx->ntok++;
		lx->buf_pos = index;
	}
	return (lst);
}

int8_t		get_index_expan(char *str, int index)
{
	if (!str)
		return (index);
	while (str[index])
	{
		if (str[index] == '?')
		{
			index++;
			break ;
		}
		if (!(str[index] == '_' || ft_isdigit(str[index])
			|| ft_isalpha(str[index])))
			break ;
		index++;
	}
	return (index);
}

t_lst		*exp_dollar_lexer(t_lexer *lx, e_pstate id, int len, t_lst *lst)
{
	char	*str;
	int		index;

	index = lx->buf_pos + len;
	str = NULL;
	(void)len;
	if (lx->buff[lx->buf_pos] == '$')
	{
		index = get_index_expan(lx->buff, index);
		if (!(str = ft_strsub(lx->buff, lx->buf_pos, index - lx->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lst, ft_lstnew(
			fetch_token(&lx->token, id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lx->ntok++;
		lx->buf_pos = index;
	}
	return (lst);
}

t_lst		*exp_tilde_lexer(t_lexer *lexer, e_pstate id, int len, t_lst *lst)
{
	char	*str;

	str = NULL;
	if (lexer->buff[lexer->buf_pos] == '~')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len)))
			return (NULL);
		if (!(ft_lstappend(&lst, ft_lstnew(
			fetch_token(&lexer->token, id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos += len;
	}
	return (lst);
}
