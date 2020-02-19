/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:13:52 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/19 19:34:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
