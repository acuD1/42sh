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

/*
** STATE CREANT LES TOKENS WORD
*/


t_lst *quote_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int i;
	char *str;


	i = lexer->buf_pos + 1;
	str = NULL;
	while (lexer->buff[i] && lexer->buff[i] != '\'')
		i++;
	i++;
	if(!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return(lexer_token);
	// if (str[0] == '$')
		// ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_EXPANSION, str), sizeof(t_token)));
	// else
		ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	// lexer->quote = 0;
	return(lexer_token);
}

t_lst *dquote_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int i;
	char *str;


	i = lexer->buf_pos + 1;
	str = NULL;
	while (lexer->buff[i] && lexer->buff[i] != '\"')
		i++;
	i++;
	if(!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return(lexer_token);
	// if (str[0] == '$')
		// ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_EXPANSION, str), sizeof(t_token)));
	// else
		ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	// lexer->quote = 0;
	return(lexer_token);
}


t_lst *word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int i;
	char *str;

	i = lexer->buf_pos;
	str = NULL;
	while (!ft_strchr(CHAR_INTERRUPT, lexer->buff[i]) && lexer->buff[i])
		i++;
	if(!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return(lexer_token);
	ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return(lexer_token);
}

t_lst		*name_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	if (lexer->buff == '\0')
	{
		lexer->status = L_END;
		return(lexer_token);
	}
	if (lexer->buff[lexer->buf_pos] == '\"')
		lexer_token = dquote_lexer(lexer, lexer_token);
	else if (lexer->buff[lexer->buf_pos] == '\'')
		lexer_token = quote_lexer(lexer, lexer_token);
	else if (ft_strchr(EXPANSION, lexer->buff[lexer->buf_pos]))
		lexer_token = expansion_lexer(lexer, lexer_token);
	else
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return(lexer_token);
}

/*
** STATE CREANT LES TOKENS IO_NUMBER
*/

static int	isvalid_ionumber(t_lexer *lexer, t_lst *lexer_token)
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
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_IONUMBER, str), sizeof(t_token)))))
			return (0);
		free(str);
		lexer->buf_pos = i;
		lexer->ntok++;
	}
	else
		return (0);
	return (1);
}

t_lst		*number_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return(lexer_token);
	}
	if (isvalid_ionumber(lexer, lexer_token))
		lexer_token = operator_lexer(lexer, lexer_token);
	else
		lexer_token = name_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return(lexer_token);
}

/*
** NEED ledition de ligne pour tester
** STATE CREANT LES TOKENS NEWLINE
*/

t_lst		*newline_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	char *str;

	str = NULL;
	if (!lexer->buff[lexer->buf_pos])
	{
		lexer->status = L_END;
		return(lexer_token);
	}
	if (lexer->buff[lexer->buf_pos] == '\n')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, 1)))
			return(lexer_token);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token, P_NEWLINE, str), sizeof(t_token)))))
			return(lexer_token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos++;
	}
	lexer->status = L_START;
	return(lexer_token);
}


// static t_lst	*create_expansions_token(t_lexer *lexer, e_parser_state id, t_lst *lexer_token)
// {	
// 	int i;
// 	t_expansion expansions[] = {
// 								{exp_tilde_lexer, P_TILDE, 1},
// 								{exp_dbparen_lexer, P_DBPARENT, 3},
// 								{exp_paren_lexer, P_PARENT, 2},
// 								{exp_bracket_lexer, P_BRACKET, 2},
// 								{exp_hook_lexer, P_HOOK, 2},
// 								{exp_dollar_lexer, P_DOLLAR, 1},
// 								};

// 	i = 0;
// 	while (i < NB_OF_EXP)
// 	{
// 		if (id == expansions[i].id)
// 		{
// 			if ((lexer_token = expansions[i].func(lexer, id, expansions[i].len, lexer_token)))
// 				return (lexer_token);
// 		}
// 		i++;
// 	}
// 	return (lexer_token);
// }