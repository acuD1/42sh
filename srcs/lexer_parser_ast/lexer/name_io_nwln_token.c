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

void		name_lexer(t_lexer *lexer)
{
	int		i;
	char	*buf;

	i = 0;
	buf = NULL;
	if (lexer->buff == '\0')
		lexer->status = END;
	else
	{
		i = lexer->buf_pos;
		while (!ft_strchr(CHAR_INTERRUPT, lexer->buff[i]) && lexer->buff[i])
			i++;
		if(!(buf = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
			return;
		if(!(ft_add_token(&lexer->tok, TOK_WORD, buf)))
			return;
		// ft_lstappend(&lexer->tok, ft_lstnew(lexer_token_set(&lexer->token, TOK_WORD, buf), sizeof(t_token)));
		lexer->ntok++;
		lexer->buf_pos = i;
		lexer->status = START;
	}
}

/*
** STATE CREANT LES TOKENS IO_NUMBER
*/

static int	isvalid_ionumber(t_lexer *lexer)
{
	int 	i;
	char	*buf;

	i = lexer->buf_pos;
	buf = NULL;
	if (!lexer->buff[i] || !ft_isdigit(lexer->buff[i]))
		return (0);
	while (ft_isdigit(lexer->buff[i]) && lexer->buff[i])
			i++;
	if ((lexer->buff[i] == '<' || lexer->buff[i] == '>'))
	{
		if (!(buf = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
			return (0);
		if(!(ft_add_token(&lexer->tok, TOK_IONUMBER, buf)))
			return (0);
		// ft_lstappend(&lexer->tok, ft_lstnew(lexer_token_set(&lexer->token, TOK_IONUMBER, buf), sizeof(t_token)));
		lexer->io_here = ft_atoi(buf);
		lexer->buf_pos = i;
		lexer->ntok++;
		free(buf);
	}
	return (1);
}

void		number_lexer(t_lexer *lexer)
{
	if (!lexer->buff)
	{
		return;
		lexer->status = END;
	}
	if (isvalid_ionumber(lexer))
		operator_lexer(lexer);
	else
		name_lexer(lexer);
	lexer->status = START;
}

/*
** NEED ledition de ligne pour tester 
** STATE CREANT LES TOKENS NEWLINE
*/

void		newline_lexer(t_lexer *lexer)
{
	char	*buf;

	buf = NULL;
	if (!lexer->buff[lexer->buf_pos])
		lexer->status = END;
	else
	{
		if (lexer->buff[lexer->buf_pos] == '\n')
		{
			if (!(buf = ft_strsub(lexer->buff, lexer->buf_pos, 1)))
				return;
			if (!(ft_add_token(&lexer->tok, TOK_NEWLINE, buf)))
				return;
			// ft_lstappend(&lexer->tok, ft_lstnew(lexer_token_set(&lexer->token, TOK_NEWLINE, buf), sizeof(t_token)));
			lexer->ntok++;
			lexer->buf_pos++;
			free(buf);
		}
	}
	lexer->status = END;
}
