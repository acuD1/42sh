/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:46:41 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 17:00:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

static const t_token	g_ope[] =
{
	{"\n", P_NEWLINE, "", 1},
	{"&&", P_ANDIF, "", 2},
	{"&>>", P_ANDDGREAT, "", 3},
	{"&>", P_ANDGREAT, "", 2},
	{"&", P_AND, "", 1},
	{"||", P_ORIF, "", 2},
	{"|", P_PIPE, "", 1},
	{";;", P_DSEMI, "", 2},
	{";", P_SEMICOLON, "", 1},
	{"<<-", P_DLESSDASH, "", 3},
	{"<<", P_DLESS, "", 2},
	{"<&", P_LESSAND, "", 2},
	{"<", P_LESS, "", 1},
	{">>", P_DGREAT, "", 2},
	{">&", P_GREATAND, "", 2},
	{">", P_GREAT, "", 1},
	{NULL, P_OPE_INTERRUPT, "", 0}
};

static t_lst			*new_ope
	(t_lexer *lx, enum e_pstate id, size_t len, t_lst *lst)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strsub(lx->buff, (unsigned int)lx->buf_pos, len)))
		return (NULL);
	ft_lstappend(&lst, ft_lstnew(
		fetch_token(&lx->token, id, str), sizeof(t_token)));
	free(str);
	lx->ntok++;
	lx->buf_pos += len;
	lx->status = L_START;
	return (lst);
}

t_lst					*operator_lexer(t_lexer *lx, t_lst *lst)
{
	size_t	i;

	i = 0;
	if (!lx->buff)
	{
		lx->status = L_END;
		return (lst);
	}
	while (g_ope[i].id != P_OPE_INTERRUPT)
	{
		if (!ft_strncmp(&lx->buff[lx->buf_pos], g_ope[i].data, g_ope[i].len))
		{
			if ((lst = new_ope(lx, g_ope[i].id, g_ope[i].len, lst)))
				break ;
		}
		i++;
	}
	lx->status = L_START;
	return (lst);
}
