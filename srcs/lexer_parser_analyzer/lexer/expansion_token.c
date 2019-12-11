/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:37:09 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 17:37:14 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static	const	t_token	g_exp[] =
{
	{P_TILDEP, "~+", 2},
	{P_TILDEM, "~-", 2},
	{P_TILDE, "~", 1},
	{P_DBPARENT, "$((", 3},
	{P_PARENT, "$(", 2},
	{P_BRACKET, "${", 2},
	{P_HOOK, "$[", 2},
	{P_DOLLAR, "$", 1},
	{P_EXP_INTERRUPT, NULL, 0}
};

t_lst					*exp_hook(t_lexer *lx, e_pstate id, int len, t_lst *lst)
{
	char		*str;
	int			index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(&lx->buff[lx->buf_pos], "$[", len))
	{
		index = lx->buf_pos;
		while (&lx->buff[index])
		{
			if (lx->buff[index] == ']')
				break ;
			index++;
		}
		index += 2;
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

t_lst					*new_exp(t_lexer *lexer, e_pstate id, t_lst *lst)
{
	int					i;
	static t_lex_exp	lex_pex[] = {
		{exp_tilde_lexer, P_TILDEP, 2},
		{exp_tilde_lexer, P_TILDEM, 2},
		{exp_tilde_lexer, P_TILDE, 1},
		{exp_dbparen, P_DBPARENT, 3},
		{exp_paren_lexer, P_PARENT, 2},
		{exp_bracket_lexer, P_BRACKET, 2},
		{exp_hook, P_HOOK, 2},
		{exp_dollar_lexer, P_DOLLAR, 1},
	};

	i = 0;
	while (i < NB_OF_EXP)
	{
		if (id == lex_pex[i].id)
		{
			if ((lst = lex_pex[i].func(lexer, id, lex_pex[i].len, lst)))
				return (lst);
		}
		i++;
	}
	return (lst);
}

t_lst					*expansion_lexer(t_lexer *lx, t_lst *lexer_token)
{
	int			i;

	i = 0;
	if (!lx->buff)
	{
		lx->status = L_END;
		return (lexer_token);
	}
	while (g_exp[i].id != P_EXP_INTERRUPT)
	{
		if (!ft_strncmp(&lx->buff[lx->buf_pos], g_exp[i].data, g_exp[i].len))
		{
			if ((lexer_token = new_exp(lx, g_exp[i].id, lexer_token)))
				return (lexer_token);
		}
		i++;
	}
	if (i == NB_OF_EXP)
		lexer_token = word_lexer(lx, lexer_token);
	lx->status = L_START;
	return (lexer_token);
}
