/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:13:21 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/07 23:23:18 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*ac_tilde(char *input, t_core *shell)
{
	t_db	*db;
	char	*tmp;

	tmp = NULL;
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
