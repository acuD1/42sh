/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:41:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/07/31 15:43:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lexer *init_lexer(t_core *shell, char *line)
{
	t_lexer *new;

	if (!line || !shell)
		return (NULL);
	if (!(new = (t_lexer*)malloc(sizeof (t_lexer*))))
		return (NULL);
	new->buff = ft_stdup(line);
	new->status = 1;
	new->ntok = 0;
	new->szbuff = ft_strlen(line);
	new->toc = NULL;
	return (new);
}

// addtok
// print token
// ft_lstappend(&shell->env, ft_lstnew(fetch_db(&shell->db, environ[i]), sizeof(t_db)));

int ft_isescaped(char c)
{
	return ((c == '\a' || c == '\b' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v') ? 1 : 0);
}

void	lexer(t_core *shell, char *line)
{
	t_lexer *lexer;
	int	*pos[2]; //0 start 1 end
	int i;

	pos[0] = 0;
	pos[1] = 0;
	i = 0;

	if (!line)
		return ;
	lexer = init_lexer(shell, line);
	while (ft_isescaped(line[i])) //skip space
		i++;
	i = 0;
	// while (ft_iscomments(line[i])) //skip commentaire
		// i++;

	while (lexer->tok->type != EOF)
	{
		//ptr sur fct qui prend lchar par char et cree les token jusqua EOF et/ou !line
		if (!line[i])

	}
}
