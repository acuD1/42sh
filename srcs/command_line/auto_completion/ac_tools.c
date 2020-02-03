/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:13:52 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/03 17:14:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		parse_env(char **prev_b, char *to_find, t_read *term)
{
	t_lst	*env;
	t_lst	*head;
	char	*tmp;

	tmp = NULL;
	env = term->shell->env;
	head = env;
	while (env)
	{
		if (isstart(((t_db *)(env->content))->key, to_find + 1)
			|| !ft_strcmp(to_find, "$"))
		{
			tmp = ft_strjoin("$", ((t_db *)(env->content))->key);
			if (read_again(prev_b, NULL, tmp, term) == FALSE)
				break ;
			term->flag = TRUE;
			ft_strdel(&tmp);
		}
		if (env->next)
			env = env->next;
		else if (term->flag == TRUE)
			env = head;
	}
	ft_strdel(&tmp);
}

/*
**		Split all bin/sbin directories in an array
*/

char		**split_path(t_core *shell, char *str)
{
	char	**array;
	t_lst	*env;

	env = shell->env;
	array = NULL;
	while (env)
	{
		if (!ft_strcmp(str, ((t_db*)(env->content))->key))
		{
			array = ft_strsplit(((t_db*)(env->content))->value, ":");
			break ;
		}
		env = env->next;
	}
	return (array);
}

u_int8_t	split_cmd(char **to_find, t_read *term)
{
	int		i;

	i = -1;
	term->ac = 0;
	while (ft_isblank(term->buffer[++i]))
		continue ;
	if (term->buffer[i] == '\0')
		return (FALSE);
	if ((term->cmd = ft_strsplit(term->buffer, SPACE)) == NULL)
		return (FALSE);
	term->ac = ft_tablen(term->cmd);
	if (term->buffer[ft_strlen(term->buffer) - 1] == ' ')
		term->ac += 1;
	if (!(*to_find = ft_strdup(term->cmd[ft_tablen(term->cmd) - 1])))
		return (FALSE);
	return (TRUE);
}
