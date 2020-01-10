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



// char *start_expansion(t_core *shell, char *data)
// {
// 	int 	i;

// 	i = 0;
// 	if (!data || !shell->env)
// 		return (data);
// 	while (i < NB_OF_EXP)
// 	{
		// if (!(ft_strncmp(data, expan[i].data, expan[i].len)))
// 			data = expan[i].machine(data, shell);
// 		i++;
// 	}
// 	return (data);
// }

uint8_t is_expansion(e_pstate id)
{
	if (id == P_TILDEP)
		return (1);
	else if (id == P_TILDEM)
		return (2);
	else if (id == P_TILDE)
		return (3);
	else if ( id == P_DBPARENT)
		return (4);
	else if ( id == P_PARENT)
		return (5);
	else if ( id == P_BRACKET)
		return (6);
	else if ( id == P_HOOK)
		return (7);
	else if (id == P_DOLLAR)
		return (8);
	else if (id == P_DBQUOTE)
		return (9);
	return (0);
}

char *no_exp(t_token *tok, t_core *shell, t_expansion *exp)
{
	(void)shell;
	(void)exp;
	return (tok->data);
}

int8_t add_assign_env(t_lst *lst, t_core *shell)
{
	char	*value;	
	t_lst	*tmp;
	
	if (!lst || !shell->env)
		return (FAILURE);
	value = NULL;
	tmp = NULL;
	while (lst)
	{
		value = ft_strdup(((t_db*)lst->content)->value);
		if (edit_var(shell, ((t_db*)lst->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (FAILURE);
		}
		tmp = lst;
		lst = lst->next;
		free(((t_db*)tmp->content)->key);
		free(tmp);
	}
	return (TRUE);
}

static char *get_exp_indbquote(char *str, t_expansion exp, t_token *tok, t_core *shell)
{
	int i;
	e_pstate state;
	char *tmp;

	i = 2;
	state = P_EXP_INTERRUPT;
	tmp = NULL;
	if (!str)
		return (tmp);
	(void)exp;
	(void)shell;
	(void)tok;
	if ((state = find_expansion(str)) != P_EXP_INTERRUPT)
	{
		// printf("%s\n", exp->sionat[state](tok, shell, exp));
		printf("state %u\n", state);
		// if ((tmp = exp.sionat[state](tok, shell, &exp)))
		// {
			// printf("le res poto %s\n", tmp);
			// return (tmp);
		// }
	}
	return (str);
}

char *exp_dbquote(t_token *tok, t_core *shell, t_expansion *exp)
{
	int 	index;
	int 	trigger;
	char 	*str;
	char 	*ret;
	char 	*new;

	if (!tok || !tok->data || !shell || !shell->env)
		return (NULL);
	printf("CA RENTRE\n");
	index = 0;
	trigger = 0;
	str = tok->data;
	new = NULL;
	ret = ft_strnew(0);
	while (str[index++] && str[index] != '\"')
	{
		if (str[index] == '$' || str[index] == '~')
		{
			get_exp_indbquote(&str[index], *exp, tok, shell);
			printf("old [%s]\n", &str[index]);
			// ret = ft_strjoinf(ret, new, 4);
		}
	}
	return (tok->data);
}

void init_expansionat(t_expansion 	*exp)
{
	exp->erience = 0;
	exp->sionat[0] = no_exp;
	exp->sionat[1] = exp_tilde;
	exp->sionat[2] = exp_tilde;
	exp->sionat[3] = exp_tilde;
	exp->sionat[4] = exp_math;
	exp->sionat[5] = exp_cmd_subs;
	exp->sionat[6] = exp_param;
	exp->sionat[7] = exp_math;
	exp->sionat[8] = exp_param;
	exp->sionat[9] = exp_dbquote;
}

void		expansion(t_core *shell, t_process *process)
{
	t_lst *lst;
	t_expansion exp;
	char *tmp;

	if (!process->tok_list || !shell)
		return ;
	tmp = NULL;
	lst = process->tok_list;
	init_expansionat(&exp);
	while (lst)
	{
		exp.erience = is_expansion(((t_token*)lst->content)->id);
		if ((tmp = exp.sionat[exp.erience](lst->content, shell, &exp)))
		{
			process->av = ft_add_arg_cmd_process(process->av, tmp);
			free (tmp);
		}
		lst = lst->next;
	}
}
