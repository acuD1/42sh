/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:50:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/20 18:43:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int8_t	parse_test(int argc, char **argv)
{
	static char	*operators[] = {"-b", "-c", "-d", "-e", "-f", "-g", "-L", "-p"
		, "-r", "-S", "-s", "-u", "-W", "-x", "-z", "=", "!=", "!", "-eq"
		, "-ne", "-ge", "-lt", "-le"}
	int			i;
	int			j;
	if (argc > 4)
		dprintf(STDERR_FILENO, "42sh: test: too many arguments");
}

int8_t			builtin_test(t_core *shell, t_process *process)
{
	return (SUCCESS);
}
