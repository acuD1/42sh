/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:21:39 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:22:02 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		ft_init_lex(t_lexer *lexer)
{
	lexer->lex[START] = start_lexer;
	lexer->lex[OPERATOR] = operator_lexer;
	lexer->lex[NAME] = name_lexer;
	lexer->lex[IO_NUMBER] = number_lexer;
	lexer->lex[NEWLINE] = newline_lexer;
	lexer->lex[ASSIGNEMENT_WORD] = assignement_word_lexer;
	lexer->lex[END] = end_lexer;
}

/*
** CELLE DU HAUT INIT LE *FCT CELLE DU BAS
** C MARKÉ DECU
*/

t_lexer			*init_lexer(t_core *shell, char *line)
{
	t_lexer		*new;

	if (!line || !shell)
		return (NULL);
	if (!(new = (t_lexer*)malloc(sizeof(t_lexer))))
		return (NULL);
	new->buff = line; //FREE LINE et dup le buff
	new->status = START;
	new->ntok = 0;
	new->buf_pos = 0;
	new->tok = NULL;
	new->io_here = 0;
	ft_init_lex(new);
	// ft_init_machine(new->machina);
	return (new);
}
