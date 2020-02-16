/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/13 20:52:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t	is_expansion(enum e_estate id)
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

int			get_exp(const char *src, int *index, char **dst, t_core *shell)
{
	t_expansion		exp;
	enum e_estate	state;
	char			*exp_tok;
	char			*exp_res;
	int				i;

	exp_tok = NULL;
	exp_res = NULL;
	state = NB_EXPANSION_STATE;
	init_expansionat(&exp);
	i = *index;
	state = find_expansion(&src[i]);
	exp.erience = is_expansion(state);
	if ((exp_tok = get_expansion(&src[i], state)))
	{
		if ((exp_res = exp.sionat[exp.erience](exp_tok, shell)))
			*dst = ft_strjoinf(*dst, exp_res, 4);
		*index += ft_strlen(exp_tok);
		ft_strdel(&exp_tok);
		return (0);
	}
	return (1);
}

void		expansion(t_core *shell, t_process *process)
{
	if (!process || !shell)
		return ;
	process->envp = set_envp(shell);
	if (process->tok_list)
		expansion_tok(shell, process);
	if (process->assign_list)
	{
		process->status = 0;
		shell->status = 0;
		expansion_assign(shell, process);
	}
	if (process->redir_list)
		expansion_redir(shell, process);
	if (process->av)
		update_last_arg(shell, process->av);
}
