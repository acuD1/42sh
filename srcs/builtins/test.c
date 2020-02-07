/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:50:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 04:22:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int32_t	get_opt_test(int argc, char **argv, int diff)
{
	static char	*op[NB_TESTBLT] = {"-b", "-c", "-d", "-e", "-f", "-g", "-L"
		, "-p", "-r", "-S", "-s", "-u", "-W", "-x", "-z", "=", "!=", "-eq"
		, "-ne", "-ge", "-lt", "-le"};
	int			i;

	i = 0;
	if (argc > 2 + diff && argv[2 + diff])
	{
		while (i <= NB_TESTBLT)
		{
			if (ft_strcmp(op[i], argv[((i <= Z_UNATEST) ? 1 : 2) + diff]) == 0)
				return (i);
			i++;
		}
	}
	return (FAILURE);
}

static int8_t	parse_testblt(int argc, char **argv, int diff, int *opt)
{
	*opt = get_opt_test(argc, argv, diff);
	if (*opt > DIFF_BINTEST
	&& ((argc > 2 + diff && ft_is_number(argv[1 + diff]) != 0)
		|| (argc > 3 + diff && ft_is_number(argv[3 + diff]) != 0)))
	{
		dprintf(STDERR_FILENO, "42sh: test: %s: integer expression expected\n"
		, (ft_is_number(argv[1 + diff]) != 0) ? argv[1 + diff] : argv[3 + diff]);
		return (FAILURE);
	}
	if ((argc > 4 + diff && *opt > Z_UNATEST)
		|| (argc > 3 + diff && *opt <= Z_UNATEST && *opt >= 0))
	{
		dprintf(STDERR_FILENO, "42sh: test: too many arguments\n");
		return (FAILURE);
	}
	if (*opt < 0 || (*opt > Z_UNATEST && argc < 4 + diff)
		|| (*opt <= Z_UNATEST && *opt >= 0 && argc > 3 + diff))
	{
		dprintf(STDERR_FILENO, "42sh: test: %s: %s operator expected\n"
		, argv[1 + diff], (*opt <= Z_UNATEST) ? "binary" : "unary");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	comp_tests(const char *s1, const char *s2, int opt)
{
	int	n1;
	int	n2;

	if (opt == SAME_BINTEST || opt == DIFF_BINTEST)
		return (((ft_strcmp(s1, s2) == 0) ? 1 : 0) ^ (DIFF_BINTEST - opt));
	n1 = ft_atoi(s1);
	n2 = ft_atoi(s2);
	if (opt == EQ_BINTEST || opt == NE_BINTEST)
		return ((n1 == n2) ^ (NE_BINTEST - opt));
	if (opt == GE_BINTEST || opt == LT_BINTEST)
		return ((n1 >= n2) ^ (LT_BINTEST - opt));
	if (n1 <= n2)
		return (0);
	return (1);
}

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
	{
		return (((argc < 2 + diff
			|| process->av[1 + diff][0] == 0) ? 1 : 0) ^ diff);
	}
	parse_testblt(argc, process->av, diff, &opt);
	if (opt <= Z_UNATEST && opt != FAILURE)
		return (path_tests(process->av[2 + diff], opt) ^ diff);
	if (opt != FAILURE)
	{
		return (comp_tests(process->av[1 + diff]
			, process->av[3 + diff], opt) ^ diff);
	}
	return (2);
}
