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

char *no_exp(char *data, t_core *shell, t_expansion *exp)
{
	(void)shell;
	(void)exp;
	return (data);
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

// char *piece_by_piece(char *exp, e_pstate id)
// {
	// if (state == P_TILDE && !ft_str)
// }

// static char *get_exp_indbquote(char *str, t_expansion exp, t_token *tok, t_core *shell)
// {
// 	int size;
// 	char *tmp;

// 	size = 0;
// 	tmp = NULL;
// 	if (!str)
// 		return (tmp);
// 	(void)exp;
// 	(void)shell;
// 	(void)tok;


// 		// printf("%s  %u\n", str, state);
// 		// if ((tmp = exp.sionat[state](tok, shell, &exp)))
// 		// {
// 			// printf("le res poto %s\n", tmp);
// 			// return (tmp);
// 		// }

// 	return (str);
// }

char	*ft_pushchar(char *s, char c)
{
	int i;
	char *new;

	i = 0;
	if (!s)
		return (NULL);
	new = NULL;
	i = ft_strlen(s);
	new = ft_strnew(i + 1);
	new = ft_strcpy(new, s);
	new[i - 1] = c;
	new[i] = '\0';
	printf("'%s;\n", new);
	return (new);
}

char *exp_dbquote(char *data, t_core *shell, t_expansion *exp)
{
	int 	index, i= 0 , z =0;
	char 	*str;
	char 	*tmp;
	char 	*tpp;
	char 	*new;
	e_pstate state;
	t_expansion toto;

	if (!data || !shell || !shell->env)
		return (NULL);
	printf("CA RENTRE\n");
	index = 0;
	init_expansionat(&toto);
	str = data;
	new = NULL;
	// tmp = ft_strsub(data, 1, 1);
	tmp = ft_strnew(0);
	tpp = ft_strnew(0);
	// state = P_EXP_INTERRUPT;
	i = ft_strlen(str);
	while (str[index++])
	{
		if (str[index] == '$' || str[index] == '~')
		{
			tpp = ft_strsub(str, 0, index);
			z = ft_strlen(&str[index]);
			state = find_expansion(&str[index]);
			toto.erience = is_expansion(state);
			if ((new = get_expansion(&str[index], state)))
				tmp = toto.sionat[toto.erience](new, shell, &toto);
			printf("old {%s} new '%s'  reload {%s}  state %u  {%d,%d}\n", &str[index], new ,tmp, state, index , z);
			// ret = ft_strjoinf(ret, new, 4);
			tpp = ft_strjoinf(tpp, tmp, 4);
		}
	}
	tmp = ft_strsub(&str[index], 0, index);
	tpp = ft_strjoinf(tpp, tmp, 4);
	printf("TMPPPP %s \n", tpp);
	(void)exp;
	return (data);
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
		if ((tmp = exp.sionat[exp.erience](((t_token*)lst->content)->data, shell, &exp)))
		{
			process->av = ft_add_arg_cmd_process(process->av, tmp);
			free (tmp);
		}
		lst = lst->next;
	}
}
