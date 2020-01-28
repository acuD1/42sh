/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:50:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/28 21:05:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int32_t	get_opt(int argc, char **argv, int diff)
{
	static char	*test_op[NB_TESTBLT] = {"-b", "-c", "-d", "-e", "-f", "-g", "-L"
		, "-p", "-r", "-S", "-s", "-u", "-W", "-x", "-z", "=", "!=", "-eq"
			, "-ne", "-ge", "-lt", "-le"};
	int			i;

	i = 0;
	if (argc > 2 + diff && argv[2 + diff])
	{
		while (i <= NB_TESTBLT)
		{
			if (ft_strcmp(test_op[i], argv[(i <= Z_UNATEST) ? 1 : 2 + diff]) == 0)
				return (i);
			i++;
		}
	}
	return (FAILURE);
}

static int8_t	parse_testblt(int argc, char **argv, int diff, int *opt)
{
	*opt = get_opt(argc, argv, diff);
	printf("%i\n", *opt);
	if ((argc > 4 + diff && *opt > Z_UNATEST)
		|| (argc > 3 + diff && *opt <= Z_UNATEST && *opt >= 0))
	{
		dprintf(STDERR_FILENO, "42sh: test: too many arguments\n");
		return (FAILURE);
	}
	else if (*opt < 0 || (*opt > Z_UNATEST && argc < 4 + diff)
		|| (*opt <= Z_UNATEST && *opt >= 0 && argc > 3 + diff))
	{
		dprintf(STDERR_FILENO, "42sh: test: %s: %s operator expected\n"
		, argv[1 + diff], (*opt <= Z_UNATEST) ? "binary" : "unary");
		return (FAILURE);
	}
	return (SUCCESS);
}
	//	dprintf(STDERR_FILENO, "42sh: test: %s: integer expression expected\n");

int8_t			builtin_test(t_core *shell, t_process *process)
{
	int		opt;
	int		argc;
	int		diff;

	(void)shell;
	argc = ft_tablen(process->av);
	diff = (argc > 1 && process->av[1]
	&& ft_strcmp(process->av[1], "!") == 0) ? 1 : 0;
	if (argc < 3 + diff)
		return ((argc < 2 + diff) ? 1 ^ diff : 0 ^ diff);
	parse_testblt(argc, process->av, diff, &opt);
	return ((opt == FAILURE) ? 2 : 0);
}
