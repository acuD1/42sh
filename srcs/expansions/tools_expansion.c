#include "sh42.h"

// void	bzero_exp_machine(t_expan machine)
// {
// 	int		index;

// 	index = 0;
// 	while (index < NB_OF_EXP)
// 	{
// 		machine[index] = exp_error;
// 		++index;
// 	}
// }

// void init_exp_machine(t_expan expan)
// {
// 	expan[0] = exp_param;
// 	expan[1] = exp_math;
// 	expan[2] = exp_cmd_subs;
// 	expan[3] = exp_param;
// 	expan[4] = exp_math;
// 	expan[5] = exp_tilde;
// 	expan[6] = exp_error;
// }

void ft_free_expansion(t_expansion *exp)
{
	if (*exp->av)
		ft_tabfree(exp->av);
}

void init_expansion(t_process *process, t_expansion *expansion)
{
	if (!process)
		return;
	expansion->av = ft_tabcopy(expansion->av, process->av);
	expansion->result = NULL;
	expansion->type = process->type;
	expansion->len = 0;
}