/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibiteurs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 23:21:22 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/25 13:02:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	update_underscore_value(char *tmp, t_core *shell, t_process *process)
{
	if (tmp)
		process->envp = add_underscore_envp(process->envp, tmp);
	(void)shell;
	ft_strdel(&tmp);
}

char	*inhibiteurs_expansion(char *data, t_core *shell, size_t flag)
{
	t_expansion		*exp;
	char			*resultat;

	if (!data || !*data)
		return (NULL);
	exp = NULL;
	resultat = NULL;
	shell->subst_error = 0;
	exp = init_expansion_inhibiteurs(exp);
	exp->heredoc = flag;
	while (exp->st != E_END)
		exp = exp->biteurs[exp->st](data, shell, exp);
	resultat = ft_strdup(exp->res);
	ft_strdel(&exp->res);
	free(exp);
	return (resultat);
}
