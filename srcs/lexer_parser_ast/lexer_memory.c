/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:22:06 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:22:08 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"


// FREE TOKEN->DATA
void	*token_set(t_token *token, e_tokenid opeid, char *data)
{
  if (token->id == TOK_WORD)
    free(token->data);
  token->id = opeid;
  if (!(token->data = ft_strdup(data))) //FREE LA DATA !!!!!!!!
  	token->data = data;
  if (data)
  	token->data_len = ft_strlen(data);
  else
  	token->data_len = 0;
  return (token);
}

static t_lst	*ft_create_token(char *data, e_tokenid opeid)
{
	t_lst *new;
	t_token *tok;

	tok = NULL;
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new->content = token_set(tok, opeid, data);
	return (new);
}

t_lst	*ft_add_token(t_lst **curr, e_tokenid opeid, char *data)
{
	t_lst		*tmp;
	t_lst		*new;

	if (!(*curr))
		return (*curr = ft_create_token(data, opeid));
	if ((*curr)->next)
	{
		new = (*curr);
		while (new->next)
			new = new->next;
		tmp = ft_create_token(data, opeid);
		tmp->prev = new;
		tmp->next = NULL;
		new->next = tmp;
	}
	else
	{
		tmp = *curr;
		tmp->next = ft_create_token(data, opeid);
		tmp->next->prev = tmp;
	}
	return (*curr);
}

void ft_printtoklist(t_lexer *lexer)
{
	t_token *tmp;

	tmp = NULL;
	if (!lexer->tok)
		return;
	printf("list avec %zu node \nAc en data        '%s' status '%u'\n", lexer->ntok, lexer->buff, lexer->status);
	while (lexer->tok)
	{
		tmp = (t_token*)lexer->tok->content;
		printf("ALLER %s %u\n", tmp->data, tmp->id);
		if (!lexer->tok->next)
			break;
		lexer->tok = lexer->tok->next;
	}
	printf("====  =====\n");
	while (lexer->tok)
	{
		tmp = (t_token*)lexer->tok->content;
		printf("RETOUR %s %u\n", tmp->data, tmp->id);
		lexer->tok = lexer->tok->prev;
	}
}
