/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/29 21:05:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char *exp_error(char *data, t_core *shell)
{
	(void)shell;
	printf("EXP_ERROR [%s]\n", data);
	return (data);
}

int8_t add_assign_env(t_core *shell, t_process *process)
{
	char	*value;
	t_lst	*tmp;
	t_lst	*ptr;
	
	value = NULL;
	tmp = NULL;
	ptr = process->assign_list;
	while (ptr)
	{
		value = ft_strdup(((t_db*)ptr->content)->value);
		if (edit_var(shell, ((t_db*)ptr->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (FAILURE);
		}
		tmp = ptr;
		ptr = ptr->next;
		free(((t_db*)tmp->content)->key);
		free(tmp);
	}
	return (TRUE);
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

// char *do_exp_in_dbquote(char *str, t_cre *shell)
// {
// 	va parcourir la str et check a chaque ~ ou $ lexpansion si ya pas dexpansion go next et join 
// }

void		find_expansion(char **tablo, t_core *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (tablo[++i])
	{
		tmp = ft_strdup(tablo[i]);
		if (tablo[i][0] == '$' || tablo[i][0] == '~')
		{
			//LEAKS
			tmp = start_expansion(shell, tmp);
			free(tablo[i]);
			tablo[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		// else if (tablo[i][0] == '\"')
		// {
		// 	tmp = do_exp_in_dbquote(tmp, shell)
		// 	free(tablo[i]);
		// 	tablo[i] = ft_strdup(tmp);
		// 	ft_strdel(&tmp);
		// }
	}
}

void		expansion(t_core *shell, t_process *process)
{
	char	**tablo;

	tablo = NULL;
	if (!process->av)
		return ;
	tablo = ft_tabcopy(tablo, process->av);
	find_expansion(tablo, shell);
	ft_tabfree(process->av);
	process->av = ft_tabcopy(process->av, tablo);
	ft_tabfree(tablo);
}
