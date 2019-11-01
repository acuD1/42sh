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
		ft_printf("[%s] {%d} \n", tmp->data, tmp->id);
		if (!lexer->tok->next)
			break;
		lexer->tok = lexer->tok->next;
	}
}

void ft_freelexerlist(t_lst **lst)
{
	t_lst *tmp;
	t_lst *node;

	if (!*lst)
		return;
	tmp = *lst;
	while (tmp)
	{
		free(((t_token*)tmp->content)->data);
		node = tmp;
		tmp = tmp->next;
		free(node);
	}
}
