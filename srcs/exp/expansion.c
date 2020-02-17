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
#include <errno.h>

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


int			check_tilde_path_exp(char *expandu, const char *str, int i, enum e_estate state)
{
	char *tmp[3];
	int len;
	int exp_size;

	tmp[0] = NULL;
	tmp[2] = NULL;
	tmp[1] = NULL;
	exp_size = i + 1;
	if (!expandu || !str || str[0] != '~')
		return (0);
	if (state != E_TILDE)
		exp_size++;
	tmp[1] = ft_strsub(str, 0, i);
	len = ft_strlen(str);
	tmp[2] = ft_strsub(str, exp_size, len - exp_size);
	tmp[0] = ft_strjoinf(tmp[1], expandu, 1);
	tmp[0] = ft_strjoinf(tmp[0], tmp[2], 2);
	if (is_a_dir(tmp[0]) == EISDIR)
	{
		ft_strdel(&tmp[0]);
		return (1);
	}
	ft_strdel(&tmp[0]);
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
		if (exp_tok[0] == '$' && !exp_tok[1])
			return (1);	
		if ((exp_res = exp.sionat[exp.erience](exp_tok, shell)))
		{
			if ((state == E_TILDEP || state == E_TILDEM || state == E_TILDE)
				&& !check_tilde_path_exp(exp_res, src, i, state))
			{
				*dst = ft_strjoin(*dst, exp_tok);
				ft_strdel(&exp_res);
			}
			else
				*dst = ft_strjoinf(*dst, exp_res, 4);
		}
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
