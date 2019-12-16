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

uint8_t is_expansion(e_pstate id)
{
	if (id == P_TILDEP || id == P_TILDEM || id == P_TILDE
			|| id == P_DBPARENT || id == P_PARENT
			|| id == P_BRACKET || id == P_HOOK ||id == P_DOLLAR)
		return (TRUE);
	return (FALSE);
}

char *exp_error(char *data, t_core *shell)
{
	(void)shell;
	printf("EXP_ERROR [%s]\n", data);
	return (data);
}

t_lst *add_assign_env(t_lst *lst, t_core *shell)
{
	char	*value;
	t_lst	*tmp;

	if (!lst || !shell->env)
		return (NULL);
	value = NULL;
	tmp = NULL;
	while (lst)
	{
		value = ft_strdup(((t_db*)lst->content)->value);
		if (edit_var(shell, ((t_db*)lst->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (lst);
		}
		tmp = lst;
		lst = lst->next;
		// free(((t_db*)tmp->content)->key);
		// free(tmp);
	}
	return (lst);
}

char *start_expansion(t_core *shell, char *data)
{
	int 	i;
	t_expan expan[] = 	{
		{exp_tilde, P_TILDE, 1, "~"},
		{exp_tilde, P_TILDEP, 2, "~+"},
		{exp_tilde, P_TILDEM, 2, "~-"},
		{exp_math, P_DBPARENT, 3, "$(("},
		{exp_cmd_subs, P_PARENT, 2, "$("},
		{exp_param, P_BRACKET, 2, "${"},
		{exp_math, P_HOOK, 2, "$["},
		{exp_param, P_DOLLAR, 1, "$"},
	};
	i = 0;
	if (!data || !shell->env)
		return (data);
	while (i < NB_OF_EXP)
	{
		if (!(ft_strncmp(data, expan[i].data, expan[i].len)))
			data = expan[i].machine(data, shell);
		i++;
	}
	return (data);
}

uint8_t 	expansion(t_core *shell, t_process *process)
{
	int 	i;
	char **tablo;
	char *tmp;

	i = -1;
	tablo = NULL;
	tmp = NULL;
//	dprintf(nono("/dev/ttys002"), "MEH");
	if (!process->av)
		return (FALSE);
	tablo = ft_tabcopy(tablo, process->av);
	while (tablo[++i])
	{
		if (tablo[i][0] == '$' || tablo[i][0] == '~')
		{
			tmp = ft_strdup(tablo[i]);
			//LEAKS
			tmp = start_expansion(shell, tmp);
			free(tablo[i]);
			tablo[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	ft_tabfree(process->av);
	process->av = ft_tabcopy(process->av, tablo);
	ft_tabfree(tablo);
	return (TRUE);
}


