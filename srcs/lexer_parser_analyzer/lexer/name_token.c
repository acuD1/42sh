/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:15:08 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 17:54:47 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		loop_till_next_quote(char *str, int *index, char quote)
{
	if (!str[*index])
		return ;
	*index += 1;
	while (str[*index] != quote)
		*index += 1;
}

int			get_word_size_ntype(int i, char *str)
{
	int		index;

	if (!str || !str[i])
		return (0);
	index = i;
	// Nope norme is fucked up here
	while (str[index] && (!ft_strchr(CHAR_INTERRUPT, str[index])))
	{
		if (str[index] == '\'')
			loop_till_next_quote(str, &index, '\'');
		if (str[index] == '`')
			loop_till_next_quote(str, &index, '`');
		if (str[index] == '\"')
			loop_till_next_quote(str, &index, '\"');
		index++;
	}
	return (index);
}

static t_lst	*word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	i = lexer->buf_pos;
	str = NULL;
	if (!(i = get_word_size_ntype(i, lexer->buff)))
		return (NULL);
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
				fetch_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	free(str);
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
