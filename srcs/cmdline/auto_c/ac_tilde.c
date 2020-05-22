/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:13:21 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/14 16:48:44 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ac_add_content(t_auto_comp *ac, char *path, char *d_name)
{
	char		*tmp;

	tmp = NULL;
	if (is_dir(path))
		tmp = ft_strjoin(d_name, "/");
	else
		tmp = ft_strjoin(d_name, " ");
	ft_lstappend(&ac->lst, ft_lstnew(tmp, sizeof(char) * (ft_strlen(tmp) + 1)));
	ac->lst_size++;
	ac->max_len = get_max_len(ac->max_len, ft_strlen(tmp));
	ft_strdel(&tmp);
}

char		*ac_tilde(char *input, t_core *shell)
{
	t_db	*db;
	char	*tmp;

	tmp = NULL;
	if (!input)
		return (NULL);
	if ((db = search_db(shell->env, "HOME")) == NULL)
		return (tmp = ft_strdup(input));
	while (ft_isblank(*input))
		input++;
	if (*input == '~')
		tmp = ft_strjoin(db->value, input + 1);
	else
		tmp = ft_strdup(input);
	return (tmp);
}
