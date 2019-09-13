/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:23:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:23:18 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

#define NB_OF_OPE 16

static const t_token    ope[] =
  {
    {TOK_NEWLINE, "\n", 1},
    {TOK_ANDIF , "&&", 2},
    {TOK_AND, "&", 1},
    {TOK_ORIF, "||", 2},
    {TOK_PIPE, "|", 1},
    {TOK_DSEMI, ";;", 2},
    {TOK_SEMICOLON, ";", 1},
    {TOK_DLESSDASH, "<<-", 3},
    {TOK_DLESS, "<<", 2},
    {TOK_LESSGREAT, "<>", 2},
    {TOK_LESSAND, "<&", 2},
    {TOK_LESS, "<", 1},
    {TOK_DGREAT, ">>", 2},
    {TOK_GREATAND, ">&", 2},
    {TOK_CLOBBER, ">|", 2},
    {TOK_GREAT, ">", 1},
    // {TOK_DBQUOTE, "\"", 1},
    // {TOK_QUOTE, "\'", 1},
    // {TOK_BQUOTE, "`", 1},
    // {TOK_PARENT_OPEN, "(", 1},
    // {TOK_PARENT_CLOSE, ")", 1},
    // {TOK_HOOK_OPEN, "[", 1},
    // {TOK_HOOK_CLOSE, "]", 1},
    // {TOK_BRACKET_OPEN, "{", 1},
    // {TOK_BRACKET_CLOSE, "}", 1},
    {TOKEN, NULL, 0}
  };

void name_lexer(t_lexer *lexer)
{
	int i;
	char *buf;

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
		lexer->ntok++;
		lexer->buf_pos = i;
		lexer->status = START;
		free(buf);
	}
}

void number_lexer(t_lexer *lexer)
{
	int i;
	char *buf;
	
	i = lexer->buf_pos;
	buf = NULL;
	if (!lexer->buff)
		lexer->status = END;
	else
	{
		while (ft_isdigit(lexer->buff[i]) && lexer->buff[i])
			i++;
		if ((lexer->buff[i] == '<' || lexer->buff[i] == '>') && i != (int)lexer->buf_pos)
		{
			if (!(buf = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
				return;
	 		if(!(ft_add_token(&lexer->tok, TOK_IONUMBER, buf)))
	 			return;
	     	lexer->io_here = ft_atoi(buf);
	     	lexer->buf_pos = i;
	     	lexer->ntok++;
	     	free(buf);
	     	operator_lexer(lexer);
		}
		else
			name_lexer(lexer);
	}
	lexer->status = START;
}

void operator_lexer(t_lexer *lexer)
{
	int i;

	i = 0;
	if (!lexer->buff)
		lexer->status = END;
	else
	{
		while (ope[i].id != TOKEN)
		{
			if (!strncmp(&lexer->buff[lexer->buf_pos], ope[i].data, ope[i].data_len))
			{
	     			if (!(ft_add_token(&lexer->tok, ope[i].id, ft_strsub(lexer->buff, lexer->buf_pos, ope[i].data_len))))
	     				return ;
			     	lexer->ntok++;
					lexer->buf_pos += ope[i].data_len;
					lexer->status = START;
					return;
	      	}
	      	i++;
		}
		if (i == NB_OF_OPE)
			name_lexer(lexer);
	}
	lexer->status = START;
}

//In the shell command language, a word consisting solely of underscores, digits, and alphabetics from the portable character set. The first character of a name is not a digit.
static int isvalid_assignement_word(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);	
	while (str[i])
	{
		if (str[i] == '_' || ft_isdigit(str[i]) || ft_isalpha(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void assignement_word_lexer(t_lexer *lexer)
{
	char *buf;
	int i;

	i = lexer->buf_pos;
	buf = NULL;
	if (!lexer->buff)
		lexer->status = END;
	else
	{
		if (ft_isdigit(lexer->buff[lexer->buf_pos]) || lexer->buff[lexer->buf_pos] == '=')
		{
			lexer->status = NAME;
			return;
		}
		while (lexer->buff[i] != '=')
			i++;
		if (!(buf = ft_strsub(lexer->buff, lexer->buf_pos, i)))
			return ;
		if (isvalid_assignement_word(buf))
		{
			if (!(ft_add_token(&lexer->tok, TOK_ASSIGN, ft_strsub(lexer->buff, lexer->buf_pos, i + 1))))
				return;
			lexer->ntok++;
			lexer->buf_pos += i + 1;
			free(buf);
		}
		else
			name_lexer(lexer);
	}
	lexer->status = START;
}
