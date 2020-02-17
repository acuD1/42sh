/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:13:52 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/17 13:36:41 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		parse_env(char **prev_b, const char *to_find, t_read *term)
{
	t_lst	*env;
	t_lst	*head;
	char	*tmp;

	tmp = NULL;
	env = term->shell->env;
	head = env;
	term->flag = FALSE;
	while (env->next)
	{
		if (ft_isstart(((t_db *)(env->content))->key, to_find + 1)
			|| !ft_strcmp(to_find, "$"))
		{
			tmp = ft_strjoin("$", ((t_db *)(env->content))->key);
			if (read_again(prev_b, NULL, tmp, term) == FALSE)
				break ;
			term->flag = TRUE;
			ft_strdel(&tmp);
		}
		env = env->next;
	}
	ft_strdel(&tmp);
	(term->flag == TRUE) ? parse_env(prev_b, to_find, term) : 0;
}

/*
**		Split all bin/sbin directories in an array
*/

char		**split_path(t_core *shell, const char *str)
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

void		split_cmd(char **to_find, t_read *term)
{
	int		i;

	i = -1;
	term->ac = 0;
	while (ft_isblank(term->buffer[++i]))
		continue ;
	if (term->buffer[i] == '\0')
	{
		*to_find = ft_strnew(0);
		term->cmd = ft_memalloc(BUFF_SIZE);
		return ;
	}
	if ((term->cmd = ft_strsplit(term->buffer, SPACE)) == NULL)
		return ;
	term->ac = ft_tablen(term->cmd);
	if (term->buffer[ft_strlen(term->buffer) - 1] == ' ')
		term->ac += 1;
	if (!(*to_find = ft_strdup(term->cmd[ft_tablen(term->cmd) - 1])))
		return ;
}
