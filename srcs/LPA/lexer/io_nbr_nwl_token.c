/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_nbr_nwl_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:55:48 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 17:00:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

static u_int8_t	filename_checker(t_lst *lst)
{
	enum e_pstate id;

	if (!lst || !lst->content)
		return (1);
	while (lst->next)
		lst = lst->next;
	id = ((t_token*)lst->content)->id;
	if (id == P_DLESSDASH || id == P_DLESS || id == P_LESS
		|| id == P_LESSAND || id == P_DGREAT
		|| id == P_GREATAND || id == P_GREAT)
		return (0);
	return (1);
}

static t_lst	*isvalid_ionumber(t_lexer *lexer, t_lst *lexer_token, size_t i)
{
	char	*str;

	str = NULL;
	if ((lexer->buff[i] == '<' || lexer->buff[i] == '>')
		&& filename_checker(lexer_token))
	{
		if (!(str = ft_strsub(lexer->buff, (unsigned int)lexer->buf_pos
			, i - lexer->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lexer->token, P_IONUMBER, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->buf_pos = i;
		lexer->ntok++;
	}
	else
		return (lexer_token = name_lexer(lexer, lexer_token));
	return (lexer_token);
}

t_lst			*number_lexer(t_lexer *lx, t_lst *lexer_token)
{
	size_t	i;

	i = lx->buf_pos;
	if (!lx->buff[lx->buf_pos] || !ft_isdigit(lx->buff[lx->buf_pos]))
	{
		lx->status = L_END;
		return (lexer_token);
	}
	while (ft_isdigit(lx->buff[i]) && lx->buff[i])
		i++;
	lexer_token = isvalid_ionumber(lx, lexer_token, i);
	lx->status = L_START;
	return (lexer_token);
}

t_lst			*newline_lexer(t_lexer *lexer, t_lst *lexer_token)
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
		if (!(str = ft_strsub(lexer->buff, (unsigned int)lexer->buf_pos, 1)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lexer->token, P_NEWLINE, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos++;
	}
	lexer->status = L_START;
	return (lexer_token);
}
