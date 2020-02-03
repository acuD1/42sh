/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:46:53 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 18:00:34 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

//Need Remov
/*
static void	ft_printtoklist(t_lst *lexer)
{
	t_token	*tmp;

	tmp = NULL;
	if (!lexer)
		return ;
	while (lexer)
	{
		tmp = (t_token*)lexer->content;
		ft_dprintf(nono("/dev/ttys002"), "{[%s] %u}\n",
			((t_token*)lexer->content)->data, ((t_token*)lexer->content)->id);
		if (!lexer->next)
			break ;
		lexer = lexer->next;
	}
	ft_dprintf(nono("/dev/ttys002"), "RETOUR\n");
	while (lexer)
	{
		tmp = (t_token*)lexer->content;
		ft_dprintf(nono("/dev/ttys002"), "{%s %u}\n",
			((t_token*)lexer->content)->data, ((t_token*)lexer->content)->id);
		if (!lexer->prev)
			break ;
		lexer = lexer->prev;
	}

}*/

//Need Remov
/*
static void	ft_freelexerlist(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*node;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			free(((t_token*)tmp->content)->data);
			free((t_token*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break ;
		}
		tmp = tmp->next;
		free(node);
	}
}
*/
