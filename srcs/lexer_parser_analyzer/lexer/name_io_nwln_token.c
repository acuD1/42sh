/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_io_nwln_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:23:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:23:18 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** STATE CREANT LES TOKENS WORD
*/

void word_token(t_lexer *lexer)
{
	int i;
	char *str;

	i = 0;
	str = NULL;
	while (!ft_strchr(CHAR_INTERRUPT, lexer->buff[i]) && lexer->buff[i])
		i++;
	if(!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return;
	if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, P_WORD, str), sizeof(t_token)))))
		return ;
	free(str);
	init_token(&lexer->token);
	lexer->ntok++;
	lexer->buf_pos = i;
}

void		name_lexer(t_lexer *lexer)
{
	if (lexer->buff == '\0')
	{
		lexer->status = L_END;
		return ;
	}
	// ft_printf("[%s] {%d} \n", &lexer->buff[lexer->buf_pos], lexer->buf_pos);
	if (ft_strchr(EXPANSION, lexer->buff[lexer->buf_pos]))
		expansion_lexer(lexer);
	else
		word_token(lexer);
	lexer->status = L_START;
}

/*
** STATE CREANT LES TOKENS IO_NUMBER
*/

static int	isvalid_ionumber(t_lexer *lexer)
{
	int 	i;
	char 	*str;

	str = NULL;
	i = lexer->buf_pos;
	if (!lexer->buff[i] || !ft_isdigit(lexer->buff[i]))
		return (0);
	while (ft_isdigit(lexer->buff[i]) && lexer->buff[i])
			i++;
	if ((lexer->buff[i] == '<' || lexer->buff[i] == '>'))
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
			return (0);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, P_IONUMBER, str), sizeof(t_token)))))
			return (0);
		free(str);
		init_token(&lexer->token);
		lexer->buf_pos = i;
		lexer->ntok++;
	}
	else
		return (0);
	return (1);
}

void		number_lexer(t_lexer *lexer)
{
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return;
	}
	if (isvalid_ionumber(lexer))
		operator_lexer(lexer);
	else
		name_lexer(lexer);
	lexer->status = L_START;
}

/*
** NEED ledition de ligne pour tester 
** STATE CREANT LES TOKENS NEWLINE
*/

void		newline_lexer(t_lexer *lexer)
{
	char *str;

	str = NULL;
	if (!lexer->buff[lexer->buf_pos])
	{
		lexer->status = L_END;
		return;
	}
	if (lexer->buff[lexer->buf_pos] == '\n')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, 1)))
			return;
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, P_NEWLINE, str), sizeof(t_token)))))
			return ;
		free(str);
		init_token(&lexer->token);
		lexer->ntok++;
		lexer->buf_pos++;
	}
	lexer->status = L_END;
}
