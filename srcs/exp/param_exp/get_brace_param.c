/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_brace_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static u_int8_t		check_special_param(char c)
{
	if (c == '?' || c == '$' || c == '!'
	|| c == '-' || c == '@' || c == '*')
		return (1);
	return (0);
}

static u_int8_t		delim_brace_param(char c)
{
	if (c == '}' || c == ':' || c == '#' || c == '%')
		return (1);
	return (0);
}

static u_int8_t		is_braceexp_valid(char *str, char *tmp, int *i, int *index)
{
	if (!(str[*i] == '#' || str[*i] == '_' || ft_isalpha(str[*i])
		|| check_special_param(str[*i])))
		return (0);
	if (str[*i] == '#')
	{
		tmp[*index] = str[*i];
		*i += 1;
		*index += 1;
	}
	if (check_special_param(str[*i]) && str[*i + 1])
	{
		tmp[*index] = str[*i];
		*i += 1;
		*index += 1;
		if (!delim_brace_param(str[*i]))
			return (0);
	}
	return (1);
}

static u_int8_t		check_n_fill(char *str, char *tmp, int *i, int *index)
{
	while (!delim_brace_param(str[*i]))
	{
		if (str[*i] == '\\')
		{
			if (str[*i + 1] && str[*i + 1] == '\n')
				*i += 2;
			else
				return (0);
		}
		if (!(str[*i] == '_' || ft_isdigit(str[*i]) || ft_isalpha(str[*i])))
			return (0);
		tmp[*index] = str[*i];
		*i += 1;
		*index += 1;
	}
	return (1);
}

char				*get_brace_param(char *str, t_core *shell)
{
	int			i;
	int			index;
	char		*tmp;

	i = 2;
	index = 0;
	tmp = ft_strnew(ft_strlen(str));
	if (!is_braceexp_valid(str, tmp, &i, &index))
		return (error_brace_param(str, shell, tmp));
	if (!check_n_fill(str, tmp, &i, &index))
		return (error_brace_param(str, shell, tmp));
	if (str[i] == ':' && str[i + 1] && !check_format_bracket(str[i + 1]))
		return (error_brace_param(str, shell, tmp));
	fill_thereste(str, tmp, &index, &i);
	tmp[index] = '\0';
	return (format_supplementaires(tmp, shell));
}
