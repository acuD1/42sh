/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:13 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 15:49:52 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*add_keys_subprompt(char c, char *str)
{
	char		key[2];

	key[0] = c;
	key[1] = '\0';
	if (!c)
		return (NULL);
	if (!str)
		str = ft_strdup(key);
	else
		str = ft_strjoinf(key, str, 2);
	return (str);
}

char			*del_keys_subprompt(char c, char *str)
{
	char		*tmp;
	size_t		len;

	tmp = NULL;
	len = 0;
	if (!c || !str)
		return (NULL);
	len = ft_strlen(str);
	if (len == 1)
		ft_strdel(&str);
	else
	{
		tmp = str;
		str = ft_strsub(tmp, 1, len - 1);
		ft_strdel(&tmp);
	}
	return (str);
}

u_int8_t		check_backslash_nbr(char *str, ssize_t *index)
{
	ssize_t		i;
	int32_t		nbr;

	i = *index;
	nbr = 0;
	if (!str[i] || str[i] != BACKSLASH)
		return (0);
	if (str[i] == BACKSLASH)
	{
		while (str[i] == BACKSLASH)
		{
			i++;
			nbr++;
		}
	}
	if ((nbr % 2) == 1)
	{
		*index = i;
		return (1);
	}
	*index = i;
	return (0);
}

void			display_subprompt(t_read *term)
{
	term->prompt_len = (ssize_t)ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->y = 0;
	term->width = term->x;
	term->x_index = term->x;
	ft_dprintf(STDERR_FILENO, "%s", term->prompt);
}

u_int8_t		sub_prompt_error(t_read *term, char sb)
{
	if (term->flag == TRUE)
	{
		ft_dprintf(STDERR_FILENO,
			"42sh: unexpected EOF while looking for matching `%c'\n", sb);
		ft_dprintf(STDERR_FILENO,
							"42sh: syntax error: unexpected end of file\n");
		term->status = CMD_DONE;
		return (TRUE);
	}
	if (term->status != CMD_SUBPROMPT)
	{
		term->status = CMD_DONE;
		return (TRUE);
	}
	return (FALSE);
}
