/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:46:53 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/19 11:46:55 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	ft_isalpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

void			ft_printtoklist(t_lexer *lexer)
{
	t_token		*tmp;

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
		if (!lexer->tok->prev)
			break;
		lexer->tok = lexer->tok->prev;
	}
}
