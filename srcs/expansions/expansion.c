/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/16 04:59:06 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t			is_expansion(e_estate id)
{
	if (id == E_TILDEP)
		return (1);
	else if (id == E_TILDEM)
		return (2);
	else if (id == E_TILDE)
		return (3);
	else if (id == E_DBPARENT)
		return (4);
	else if (id == E_PARENT || id == E_BQUOTE)
		return (5);
	else if (id == E_BRACKET)
		return (6);
	else if (id == E_HOOK)
		return (7);
	else if (id == E_DOLLAR)
		return (8);
	else if (id == E_DBQUOTE)
		return (9);
	else if (id == E_QUOTE)
		return (0);
	return (0);
}

int				expelliarmus(char *src, int *index, char **dst, t_core *shell)
{
	t_expansion	toto;
	e_estate	state;
	char		*hetero;
	char		*trans;
	int			i;

	hetero = NULL;
	trans = NULL;
	state = NB_EXPANSION_STATE;
	init_expansionat(&toto);
	i = *index;
	state = find_expansion(&src[i]);
	toto.erience = is_expansion(state);
	if ((hetero = get_expansion(&src[i], state)))
	{
		if ((trans = toto.sionat[toto.erience](hetero, shell)))
			*dst = ft_strjoinf(*dst, trans, 4);
		*index += ft_strlen(hetero);
		return (0);
		ft_strdel(&hetero);
	}
	return (1);
}

void			expansion(t_core *shell, t_process *process)
{
	if (!process || !shell)
		return ;
	process->envp = set_envp(shell);
	if (process->tok_list)
		expansion_tok(shell, process);
	if (process->assign_list)
		expansion_assign(shell, process);
	if (process->redir_list)
		expansion_redir(shell, process);
}
