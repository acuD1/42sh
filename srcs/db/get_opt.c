/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:34:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/28 00:09:33 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	[BETA] The get_opt fonction parses char **av in main. Fill shell->opt and
**	print_opt execute them. If option not valid then print usage.
*/

static int8_t	usage(const char *av, int i)
{
	while (av[i])
	{
		if (!(ft_strchr("-vh", av[i])))
		{
			dprintf(STDERR_FILENO, "42sh: illegal option -%c\n", av[i]);
			ft_putendl_fd("usage : ./42sh [-vh]", STDERR_FILENO);
			break ;
		}
		i++;
	}
	return (FAILURE);
}

static int8_t	fill_opt(t_core *shell, const char av)
{
	if (!(ft_strchr("-vh", av)))
		return (FAILURE);
	if (av == 'v')
		shell->opt |= OPT_VERS;
	else if (av == 'h')
		shell->opt |= OPT_HELP;
	return (SUCCESS);
}

int8_t			get_opt(int ac, char **av, t_core *shell)
{
	int		i;
	size_t	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] == '-' && av[i][2])
			return (usage(av[i], i));
		else if (av[i][0] == '-' && av[i][1] == '-')
		{
			i++;
			break ;
		}
		else if (av[i][0] == '-')
		{
			while (av[i][j])
				if (fill_opt(shell, av[i][j++]) == FAILURE)
					return (usage(av[i], i));
		}
		else
			break ;
	}
	/* open_logger_fd(shell, av[i]); # Maybe for futur logger implementation */
	return (SUCCESS);
}
