/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:24 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 06:35:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

int		discard_backslash(const char *data, int *i, char **res)
{
	int		backslash_nbr;
	int		index;
	int		ret;
	char	*tmp;

	index = *i;
	backslash_nbr = 0;
	tmp = NULL;
	ret = 0;
	if (data[index] == '\\')
	{
		while (data[index] == '\\')
		{
			index++;
			backslash_nbr++;
		}
		ret = backslash_nbr % 2;
		backslash_nbr /= 2;
		tmp = ft_strsub(data, index - backslash_nbr, backslash_nbr);
		*res = ft_strjoinf(*res, tmp, 4);
		if (data[index] == '\n')
			index++;
		*i = index;
	}
	return (ret);
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

void			apply_expansion(char *data, char *token, t_core *shell, t_expansion *exp)
{
	char		*res;

	res = NULL;
	if ((res = exp->sionat[exp->erience](token, shell)))
	{
		if ((exp->st == E_TILDEP || exp->st == E_TILDEM || exp->st == E_TILDE)
			&& !check_tilde_path_exp(res, data, exp->index, exp->st))
		{
			exp->res = ft_strjoinf(exp->res, token, 1);
			ft_strdel(&res);
		}
		else
			exp->res = ft_strjoinf(exp->res, res, 4);
	}
}

t_expansion 	*exp_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	char			*exp_tok;

	exp_tok = NULL;
	exp->st = find_expansion(&data[exp->index]);
	exp->erience = is_expansion(exp->st);
	if ((exp_tok = get_expansion(&data[exp->index], exp->st)))
	{
		if (exp_tok[0] == '$' && !exp_tok[1])
		{
			exp->st = E_WORD;
			return (exp);
		}
		apply_expansion(data, exp_tok, shell, exp);
		exp->index += ft_strlen(exp_tok);
		ft_strdel(&exp_tok);
	}
	exp->st = (!data[exp->index]) ? E_END : E_START;
	return (exp);
}

t_expansion 	*word_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	char *tmp;

	if (!data[exp->index])
	{
		exp->st = E_END;
		return (exp);
	}
	tmp = ft_strsub(data, exp->index, 1);
	exp->res = ft_strjoinf(exp->res, tmp, 4);
	exp->index++;
	exp->st = (!data[exp->index]) ? E_END : E_START;
	(void)shell;
	return (exp);
}

t_expansion 	*quotes_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	exp->quotus = skip_quotes(data, exp);
	exp->st = (!data[exp->index]) ? E_END : E_START;
	(void)shell;
	return (exp);
}

t_expansion 	*discard_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	(void)shell;
	exp->discarded = discard_backslash(data, &(exp->index), &(exp->res));
	exp->st = (!data[exp->index]) ? E_END : E_START;
	return (exp);
}

int 			quotes_condition(char c, enum e_estate state)
{
	if ((c == '\"' && state == E_QUOTE) || (c == '\'' && state == E_DBQUOTE))
		return (0);
	return (1);
}

t_expansion 	*start_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	if (!data[exp->index])
		exp->st = E_END;
	else if (exp->quotus != E_QUOTE && data[exp->index] == '\\')
		exp->st = E_DISCARD;
	else if (!exp->discarded && quotes_condition(data[exp->index], exp->quotus)
		&& (data[exp->index] == '\'' || data[exp->index] == '\"'))
		exp->st = E_QUOTES;
	else if ((!exp->discarded && exp->quotus != E_QUOTE)
		&& ((data[exp->index] == '$' || data[exp->index] == '~' || data[exp->index] == '`')))
		exp->st = E_EXP;
	else
		exp->st = E_WORD;
	exp->discarded = 0;
	(void)shell;
	return (exp);
}

t_expansion	*init_expansion_inhibiteurs(t_expansion *exp)
{
	if (!(exp = (t_expansion*)malloc(sizeof(t_expansion))))
		return (NULL);
	exp->index = 0;
	exp->discarded = 0;
	exp->res = ft_strnew(0);
	exp->st = E_START;
	exp->quotus = NB_EXPANSION_STATE;
	init_expansion_machine(exp);
	exp->biteurs[E_START] = start_biteurs;
	exp->biteurs[E_EXP] = exp_biteurs;
	exp->biteurs[E_WORD] = word_biteurs;
	exp->biteurs[E_QUOTES] = quotes_biteurs;
	exp->biteurs[E_DISCARD] = discard_biteurs;
	exp->erience = 0;
	return (exp);
}

char		*quote_backslash_discarder(char *data)
{
	char			*res;
	char			*tmp;
	int				index;
	enum e_estate	st;

	st = NB_EXPANSION_STATE;
	if (!data)
		return (NULL);
	tmp = NULL;
	res = NULL;
	index = 0;
	while (data[index])
	{
		st = skip_recur_quote(data, &index, st);
		if (!data[index])
			break ;
		if (st != E_QUOTE)
			discard_backslash(data, &index, &res);
		if (res)
		{
			tmp = ft_strsub(data, index, 1);
			res = ft_strjoinf(res, tmp, 4);
		}
		else
			res = ft_strsub(data, index, 1);
		index++;
	}
	return (res);
}

char		*inhibiteurs_expansion(char *data, t_core *shell)
{
	t_expansion	*exp;
	char *resultat;

	if (!data || !*data)
		return (NULL);
	exp = NULL;
	resultat = NULL;
	exp = init_expansion_inhibiteurs(exp);
	while (exp->st != E_END)
		 exp = exp->biteurs[exp->st](data, shell, exp);
	resultat = ft_strdup(exp->res);
	ft_strdel(&exp->res);
	free(exp);
	return (resultat);
}
