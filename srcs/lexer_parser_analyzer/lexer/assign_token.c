/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:45:53 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/19 11:45:57 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** In the shell command language, a word consisting solely of underscores, digits, and alphabetics
** The first character of a name is not a digit.
*/

static	int isvalid_assignement_word(char *str, size_t index)
{
	int i;

	i = index;
	if (!str || ft_isdigit(str[0]) || str[0] == '=')
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

/*
** STATE CREANT LES TOKEN ASSIGN
*/

static int create_assign_token(t_lexer *lexer, int len)
{
	char *str;

	str = NULL;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len - lexer->buf_pos)))
		return (0);
	if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, P_ASSIGN, str), sizeof(t_token)))))
		return (0);
	free(str);
	init_token(&lexer->token);
	lexer->ntok++;
	lexer->buf_pos = len;
	return (1);
}

void		assignement_word_lexer(t_lexer *lexer)
{
	int i;

	i = 0;
	if (!lexer->buff)
		lexer->status = L_END;
	else
	{
		if ((i = isvalid_assignement_word(lexer->buff, lexer->buf_pos)))
			create_assign_token(lexer, i);
		else
			name_lexer(lexer);
	}
	lexer->status = L_START;
}
