#include "sh42.h"

// static char	*create_expansions_token(char *expansions, t_token *exp_token, t_core *shell)
// {	
// 	int i;
// 	t_expansion expansions[] = {
// 								{exp_tilde_exp, P_TILDE, 1},
// 								{exp_dbparen_exp, P_DBPARENT, 3},
// 								{exp_paren_exp, P_PARENT, 2},
// 								{exp_bracket_exp, P_BRACKET, 2},
// 								{exp_hook_exp, P_HOOK, 2},
// 								{exp_dollar_exp, P_DOLLAR, 1},
// 								};

// 	i = 0;
// 	while (i < NB_OF_EXP)
// 	{
// 		if (id == expansions[i].id)
// 		{

// 			if ((lexer_token = 	// while (i < NB_OF_EXP)
	// {
		// if (!ft_strncmp(expansion, quotes[i].data, quotes[i].data_len))
		// {
		// 	return(get_expansion_commeunguedin(expansion, exp[quotes[i].id].func(quotes, expansion, shell)));
		// }
		// i++;
	// }))
// 				return (lexer_token);
// 		}
// 		i++;
// 	}
// 	return (lexer_token);
// }

// char *get_expansion_commeunguedin(char *expansion, func(t_token*, char*, t_core *))
// {
// 	printf("totototo\n");
// }

char *start_expansion(char *data, t_core *shell, t_expansion *expansion)
{
	// static t_token    quotes[] =
	// 					{
	// 						{P_TILDE, "~", 1},
	// 						{P_DBPARENT, "$((", 3},
	// 						{P_PARENT, "$(", 2},
	// 						{P_BRACKET, "${", 2},
	// 						{P_HOOK, "$[", 2},
	// 						{P_DOLLAR, "$", 1},
	// 						{P_EXP_INTERRUPT, NULL, 0}
	// 					};

	printf("%s\n", data);
	// while (new_exp[i])
	// {		
	// 	if (new_exp[i] == '~')
	// 		return (exp_tilde(&(quotes[0]), new_exp, shell));
	// 	if (new_exp[i] == '$')
	// 		return (exp_tilde(&(quotes[0]), new_exp, shell));
	// 		// return (exp_dollar(&(quotes[5]), new_exp, shell));
	// 	else
	// 	{
	// 		index++;
	// 		break;
	// 	}
	// 	i++;
	// }
	return (expansion->result);
	(void)shell;
}

static void	bzero_exp_machine(t_exp machine)
{
	int		index;

	index = 0;
	while (index < NB_OF_EXP)
	{
		machine[index] = exp_error;
		++index;
	}
}

void init_exp_machine(t_exp machine)
{
	machine[0] = exp_dollar;
	machine[1] = exp_dbparen;
	machine[2] = exp_paren;
	machine[3] = exp_bracket;
	machine[4] = exp_hook;
	machine[5] = exp_tilde;
}

void init_expansion(t_process *process, t_expansion *expansion)
{
	expansion->av = process->av;
	expansion->result = ft_strnew(0);
	expansion->id = process->type;
	expansion->len = 0;
	bzero_exp_machine(expansion->machine);
	init_exp_machine(expansion->machine);
	// expansion->exp = init_expansion_exp();
}

uint8_t 	expansion(t_core *shell, t_process *process)
{
	int 	i;
	int 	j;
	t_expansion expansion;

	i = 0;
	j = 0;
	if (!process->av)
		return (FALSE);
	init_expansion(process, &expansion);
	while (process->av[i])
	{
		while (process->av[i][j])
		{
			if (process->av[i][0] == '$' || process->av[i][0] == '~')
				process->av[i] = start_expansion(process->av[i], shell, &expansion);
			else
				j++;
		}
		i++;
	}
	return (TRUE);
	// if (i == NB_OF_EXP)
	// 	process_token = word_process(process, process_token);
	// process->status = L_START;
}


