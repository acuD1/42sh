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

char 		*exp_math(char *expansion, t_core *shell, e_parser_state id)
{
	(void)shell;
	printf("EXP_DBPARENT [%s %u]\n", expansion, id);
	return (NULL);
}

char 		*exp_cmd_subs(char *expansion, t_core *shell, e_parser_state id)
{
	(void)shell;
	printf("EXP_PARENT [%s %u]\n", expansion, id);
	return (NULL);
}

char 		*exp_param(char *expansion, t_core *shell, e_parser_state id)
{
	(void)shell;
	printf("EXP_DOLLAR [%s %u]\n", expansion, id);
	return (NULL);
}

char 		*exp_tilde(char *expansion, t_core *shell, e_parser_state id)
{
	(void)shell;
	printf("EXP_TILDE [%s %u]\n", expansion, id);
	return (NULL);
}

char 		*exp_error(char *expansion, t_core *shell, e_parser_state id)
{
	(void)shell;
	printf("EXP_ERROR [%s %u]\n", expansion, id);
	return (NULL);
}

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
	// return (expansion->result);
	// (void)shell;
char *start_expansion(t_core *shell, t_expansion *expansion, char *data)
{
	printf("MEG %s\n", data);
	(void)shell;
	(void)expansion;
	return (NULL);
}

void	bzero_exp_machine(t_expan machine)
{
	int		index;

	index = 0;
	while (index < NB_OF_EXP)
	{
		machine[index] = exp_error;
		++index;
	}
}

void init_exp_machine(t_expan machine)
{
	machine[0] = exp_param;
	machine[1] = exp_math;
	machine[2] = exp_cmd_subs;
	machine[3] = exp_param;
	machine[4] = exp_math;
	machine[5] = exp_tilde;
	machine[6] = exp_error;
}

int getnb_exp(e_parser_state id)
{
	if (id == P_DOLLAR)
		return (0);
	else if (id == P_DBPARENT)
		return (1);
	else if (id == P_PARENT)
		return (2);
	else if (id == P_BRACKET)
		return (3);
	else if (id == P_HOOK)
		return (4);
	else if (id == P_TILDE)
		return (5);
	return (6);
}

void init_expansion(t_process *process, t_expansion *expansion)
{
	if (!process)
		return;
	if (!(expansion = (t_expansion*)malloc(sizeof(t_expansion))))
		return;
	expansion->av = process->av;
	expansion->result = ft_strnew(0);
	expansion->type = process->type;
	expansion->len = 0;
	// bzero_exp_machine(&expansion->machine);
	init_exp_machine(&expansion->machine);
}

uint8_t 	expansion(t_core *shell, t_process *process)
{
	int 	i;
	t_expansion *expansion;

	i = -1;
	if (!process->av)
		return (FALSE);
	expansion = NULL;
	init_expansion(process, expansion);
	while (process->av[++i])
	{
		if (process->av[i][0] == '$' || process->av[i][0] == '~')
			start_expansion(shell, expansion, process->av[i]);
	}
	// ft_free(expansion);
	return (TRUE);
}


