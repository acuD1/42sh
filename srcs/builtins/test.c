/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:50:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/05/28 15:51:53 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static int32_t	get_opt_test(char *str)
{
	static char	*op[NB_TESTBLT] = {"-b", "-c", "-d", "-e", "-f", "-g", "-L"
		, "-p", "-r", "-S", "-s", "-u", "-w", "-x", "-z", "=", "!=", "-eq"
		, "-ne", "-ge", "-lt", "-le"};
	size_t		i;

	i = 0;
	while (i < NB_TESTBLT)
	{
		if (ft_strcmp(op[i], str) == 0)
			return ((int32_t)i);
		i++;
	}
	return (FAILURE);
}

static void		parse_testblt_handler
	(char **argv, int8_t diff, int64_t num, u_int8_t status)
{
	if (status == TEST_INT_EXP)
		ft_dprintf(2, "42sh: test: %s: integer expression expected\n"
			, (ft_atol(argv[1 + diff], &num) != SUCCESS)
			? argv[1 + diff] : argv[3 + diff]);
	else if (status == TEST_ARG)
		ft_dprintf(STDERR_FILENO, "42sh: test: too many arguments\n");
	else if (status == TEST_BIN)
		ft_dprintf(STDERR_FILENO, "42sh: test: %s: %s operator expected\n"
			, argv[1 + diff], "binary");
	else if (status == TEST_UNA)
		ft_dprintf(STDERR_FILENO, "42sh: test: %s: %s operator expected\n"
			, argv[1 + diff], "unary");
}

static int8_t	parse_testblt
	(size_t argc, char **argv, int8_t diff, int32_t *opt)
{
	int64_t	num;

	num = 0;
	if ((int)argc > 4 + diff)
		parse_testblt_handler(argv, diff, num, TEST_ARG);
	else if ((int)argc == 4 + diff)
	{
		if ((*opt = get_opt_test(argv[2 + diff])) == FAILURE
		|| *opt <= Z_UNATEST)
			parse_testblt_handler(argv, diff, num, TEST_BIN);
		else if (*opt >= EQ_BINTEST && *opt <= LE_BINTEST
		&& (ft_atol(argv[1 + diff], &num) != SUCCESS
			|| ft_atol(argv[3 + diff], &num) != SUCCESS))
			parse_testblt_handler(argv, diff, num, TEST_INT_EXP);
		else
			return (SUCCESS);
	}
	else if ((int)argc == 3 + diff
	&& (*opt = get_opt_test(argv[1 + diff])) == FAILURE)
		parse_testblt_handler(argv, diff, num, TEST_UNA);
	else
		return (SUCCESS);
	return (FAILURE);
}

static int8_t	comp_tests(const char *s1, const char *s2, int32_t opt)
{
	int64_t n1;
	int64_t	n2;

	if (opt == SAME_BINTEST || opt == DIFF_BINTEST)
	{
		return (((ft_strcmp(s1, s2) == 0)
		? 1 : 0) ^ (int8_t)(DIFF_BINTEST - opt));
	}
	if (!s1 || !s2)
		return (1);
	ft_atol(s1, &n1);
	ft_atol(s2, &n2);
	if (opt == EQ_BINTEST || opt == NE_BINTEST)
		return ((n1 == n2) ^ (int8_t)(NE_BINTEST - opt));
	if (opt == GE_BINTEST || opt == LT_BINTEST)
		return ((n1 >= n2) ^ (int8_t)(LT_BINTEST - opt));
	if (n1 <= n2)
		return (0);
	return (1);
}

int8_t			builtin_test(t_core *shell, t_process *process)
{
	int32_t	opt;
	size_t	argc;
	int8_t	diff;

	(void)shell;
	argc = ft_tablen(process->av);
	diff = (argc > 1 && process->av[1]
	&& ft_strcmp(process->av[1], "!") == 0) ? 1 : 0;
	if (argc < 3 + (size_t)diff)
	{
		return (((argc < 2 + (size_t)diff
			|| process->av[1 + diff][0] == 0) ? 1 : 0) ^ diff);
	}
	if (parse_testblt(argc, process->av, diff, &opt) == FAILURE)
		return (2);
	if (opt <= Z_UNATEST && opt != FAILURE)
		return (path_tests(process->av[2 + diff], opt) ^ diff);
	return (comp_tests(process->av[1 + diff]
			, process->av[3 + diff], opt) ^ diff);
}
