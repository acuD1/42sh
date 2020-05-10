/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:24 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/12 15:31:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

u_int8_t		check_tilde_path_exp
	(char *expandu, const char *str, size_t i)
{
	char			*tmp[2];

	tmp[0] = NULL;
	tmp[1] = NULL;
	if (!expandu || !str || str[0] != '~')
		return (0);
	tmp[0] = ft_strsub(str, 0, i);
	i = (str[i] == '~' && str[i + 1]
		&& (str[i + 1] == '-' || str[i + 1] == '+')) ? i + 2 : i + 1;
	tmp[1] = ft_strsub(str, (unsigned int)i, ft_strlen(str) - i);
	if ((tmp[1][0] == '/' || tmp[1][0] == ':') && !*tmp[0])
	{
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
		return (1);
	}
	tmp[0] = ft_strjoinf(tmp[0], expandu, 1);
	tmp[0] = ft_strjoinf(tmp[0], tmp[1], 3);
	if (is_a_dir(tmp[0]) == EISDIR)
	{
		ft_strdel(&tmp[0]);
		return (1);
	}
	ft_strdel(&tmp[0]);
	return (0);
}

static void		apply_expansion
	(char *data, char *token, t_core *shell, t_expansion *exp)
{
	char	*res;

	res = NULL;
	if ((res = exp->sionat[exp->erience](token, shell)))
	{
		if ((exp->st == E_TILDEP || exp->st == E_TILDEM || exp->st == E_TILDE)
			&& !check_tilde_path_exp(res, data, exp->index))
		{
			exp->res = ft_strjoinf(exp->res, token, 1);
			ft_strdel(&res);
		}
		else
			exp->res = ft_strjoinf(exp->res, res, 4);
	}
}

t_expansion		*exp_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	char	*exp_tok;

	exp_tok = NULL;
	exp->st = find_expansion(&data[exp->index]);
	exp->erience = is_expansion(exp->st);
	if ((exp_tok = get_expansion(&data[exp->index], exp->st)))
	{
		if (exp_tok[0] == '$' && !exp_tok[1])
		{
			exp->st = E_WORD;
			ft_strdel(&exp_tok);
			return (exp);
		}
		apply_expansion(data, exp_tok, shell, exp);
		exp->index += ft_strlen(exp_tok);
		ft_strdel(&exp_tok);
	}
	exp->st = (!data[exp->index]) ? E_END : E_START;
	return (exp);
}

t_expansion		*word_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	char	*tmp;

	if (!data[exp->index])
	{
		exp->st = E_END;
		return (exp);
	}
	tmp = ft_strsub(data, (unsigned int)exp->index, 1);
	exp->res = ft_strjoinf(exp->res, tmp, 4);
	exp->index++;
	exp->st = (!data[exp->index]) ? E_END : E_START;
	(void)shell;
	return (exp);
}

t_expansion		*start_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	if (!data[exp->index] || shell->subst_error)
		exp->st = E_END;
	else if (exp->quotus != E_QUOTE && data[exp->index] == '\\')
		exp->st = E_DISCARD;
	else if (!exp->discarded && !exp->heredoc
		&& quotes_condition(data[exp->index], exp->quotus)
		&& (data[exp->index] == '\'' || data[exp->index] == '\"'))
		exp->st = E_QUOTES;
	else if (!exp->discarded && (exp->quotus != E_QUOTE || exp->heredoc)
		&& data[exp->index] == '$')
		exp->st = E_EXP;
	else if (!exp->discarded && !exp->heredoc
		&& exp->quotus != E_QUOTE && data[exp->index] == '~')
		exp->st = E_EXP;
	else
		exp->st = E_WORD;
	exp->discarded = 0;
	return (exp);
}
