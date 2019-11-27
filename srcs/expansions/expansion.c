#include "sh42.h"

uint8_t is_expansion(enum parser_state id)
{
	if (id == P_TILDEP || id == P_TILDEM || id == P_TILDE
		|| id == P_DBPARENT || id == P_PARENT
		|| id == P_BRACKET || id == P_HOOK ||id == P_DOLLAR)
		return (TRUE);
	return (FALSE);
}

char *exp_error(char *data, t_core *shell)
{
	(void)shell;
	printf("EXP_ERROR [%s]\n", data);
	return (data);
}

char *start_expansion(t_core *shell, char *data)
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
	if (!data || !shell->env)
		return (data);
	while (i < NB_OF_EXP)
	{
		if (!(ft_strncmp(data, expan[i].data, expan[i].len)))
			data = expan[i].machine(data, shell);
		i++;
	}
	return (data);
}

uint8_t 	expansion(t_core *shell, t_process *process)
{
	int 	i;
	char **tablo;
	char *tmp;

	i = -1;
	tablo = NULL;
	tmp = NULL;
	if (!process->av)
		return (FALSE);
	tablo = ft_tabcopy(tablo, process->av);
	while (tablo[++i])
	{
		if (tablo[i][0] == '$' || tablo[i][0] == '~')
		{
			tmp = ft_strdup(tablo[i]);
			tmp = start_expansion(shell, tmp);
			free(tablo[i]);
			tablo[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
	ft_tabfree(process->av);
	process->av = ft_tabcopy(process->av, tablo);
	ft_tabfree(tablo);
	return (TRUE);
}


