#include "sh42.h"

char *exp_error(char *data, t_core *shell, t_expansion *expansion)
{
	(void)shell;
	printf("EXP_ERROR [%s %u]\n", data, expansion->type);
	return (data);
}

char *start_expansion(t_core *shell, t_expansion *expansion, char *data)
{
	int 	i;
	t_expan expan[] = 	{
							{exp_tilde, P_TILDE, 1, "~"},
							{exp_tilde, P_TILDEP, 2, "~+"},
							{exp_tilde, P_TILDEM, 2, "~-"},
							{exp_math, P_DBPARENT, 3, "$(("},
							{exp_cmd_subs, P_PARENT, 2, "$("},
							{exp_param, P_BRACKET, 2, "${"},
							{exp_math, P_HOOK, 2, "$["},
							{exp_param, P_DOLLAR, 1, "$"},
						};
	i = 0;
	if (!data || !*expansion->av || !shell->env)
		return (data);
	while (i < NB_OF_EXP)
	{
		if (!(ft_strncmp(data, expan[i].data, expan[i].len)))
		{
			expansion->type = expan[i].id;
			expansion->len = expan[i].len;
			if ((data = expan[i].machine(data, shell, expansion)))
				return (data);
		}
		i++;
	}
	return (data);
}

uint8_t 	expansion(t_core *shell, t_process *process)
{
	int 	i;
	t_expansion expansion;

	i = -1;
	if (!process->av)
		return (FALSE);
	init_expansion(process, &expansion);
	while (expansion.av[++i])
	{
		if (expansion.av[i][0] == '$' || expansion.av[i][0] == '~')
			if (!(expansion.av[i] = start_expansion(shell, &expansion, expansion.av[i])))
				return (FALSE);
	}
	ft_tabfree(process->av);
	process->av = ft_tabcopy(process->av, expansion.av);
	ft_tabfree(expansion.av);
	return (TRUE);
}


