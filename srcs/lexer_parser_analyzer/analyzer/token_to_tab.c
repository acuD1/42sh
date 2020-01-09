/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:18 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:19 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	**create_tablo(char *str)
{
	char	**tablo;

	if (!str)
		return (NULL);
	tablo = NULL;
	if (!(tablo = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	tablo[0] = ft_strdup(str);
	tablo[1] = NULL;
	return (tablo);
}

char		**ft_add_arg_cmd_process(char **tablo, char *str)
{
	char	**tb;
	int		j;

	j = 0;
	tb = NULL;
	if (!str)
		return (NULL);
	if (!tablo)
		return (tablo = create_tablo(str));
	if (!(tb = (char**)malloc(sizeof(char*) * (ft_tablen(tablo) + 2))))
		return (NULL);
	while (tablo[j])
	{
		tb[j] = ft_strdup(tablo[j]);
		free(tablo[j]);
		j++;
	}
	tb[j] = ft_strdup(str);
	tb[j + 1] = NULL;
	free(tablo);
	return (tb);
}

char		*fill_cmd_job(t_token *token, int flag, char *cmd)
{
	char	*str;

	str = NULL;
	if (token->id == 0 || !flag)
		str = ft_strdup(token->data);
	else
		str = ft_strjoin(((t_token*)token)->data, " ");
	cmd = ft_strjoinf(cmd, str, 4);
	return (cmd);
}