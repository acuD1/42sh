/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/28 16:06:29 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*add_last_output(t_auto_comp *ac, char *input)
{
	char	*start;
	char	*output;
	size_t	i;

	output = (char *)ac->lst->content;
	if (ac->type == AC_VARIABLE)
		output++;
	if (ac->type == AC_BRACKET)
		output += 2;
	if (input == NULL || output == NULL || *output == '\0')
		return (NULL);
	start = input + ac->x;
	i = 0;
	if (start[ft_strlen(start) - 1] == '/')
		return (ft_strdup(output));
	while (output[i] != '\0')
	{
		if (start[i] != output[i])
			return (ft_strdup(output + i));
		i++;
	}
	return (NULL);
}

static int8_t	complete_slash(char **output)
{
	if (!*output)
		return (FALSE);
	if (is_dir(*output) && !last_is_slash(*output))
	{
		ft_strdel(output);
		*output = ft_strdup("/");
		return (TRUE);
	}
	return (FALSE);
}

static char		*get_output(char **input, t_core *shell,
							t_auto_comp *ac, char **output)
{
	static	t_ac_fct	*get_output[] = {ac_file, ac_binary,
						ac_variable, ac_variable};
	char				*tmp;

	tmp = NULL;
	if (is_dot(*input))
	{
		*output = ft_strdup("/");
		return (*output);
	}
	ac->type = ac_check_type(*input);
	*output = ac_parse_input(*input, ac->type);
	ac->x = ft_strlen(*input) - ft_strlen(*output);
	*output = ac_tilde(*output, shell);
	tmp = ft_strsub(*input, 0, ft_strlen(*input) - (ft_strlen(*input) - ac->x));
	*input = ft_strjoinf(tmp, *output, 1);
	if (complete_slash(output) == TRUE)
	{
		ft_strdel(input);
		return (*output);
	}
	get_output[ac->type](*output, ac, shell);
	return (NULL);
}

static int8_t	display_last_output(t_auto_comp *ac, char *input, char **output)
{
	ft_strdel(output);
	if (ac->lst_size == TRUE)
	{
		*output = add_last_output(ac, input);
		ft_strdel(&input);
		return (SUCCESS);
	}
	ft_strdel(&input);
	display_ac_lst(ac);
	if (ac->lst_size == 0)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			auto_complete_mode(char *input, t_core *shell, char **output)
{
	static t_auto_comp	ac;
	char				*saved;

	(void)shell;
	free_lst(ac.lst);
	ft_bzero(&ac, sizeof(ac));
	if (shell->ac_flag == FAILURE)
		return (SUCCESS);
	saved = input;
	if (get_output(&saved, shell, &ac, output) != NULL)
		return (SUCCESS);
	if (display_last_output(&ac, saved, output) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
