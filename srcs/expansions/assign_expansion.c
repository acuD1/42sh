#include "sh42.h"


int8_t add_assign_env(t_lst *lst, t_core *shell)
{
	char	*value;	
	t_lst	*tmp;
	
	if (!lst || !shell->env)
		return (FAILURE);
	value = NULL;
	tmp = NULL;
	while (lst)
	{
		value = ft_strdup(((t_db*)lst->content)->value);
		if (edit_var(shell, ((t_db*)lst->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (FAILURE);
		}
		tmp = lst;
		lst = lst->next;
		free(((t_db*)tmp->content)->key);
		free(tmp);
	}
	return (TRUE);
}

void		expansion_assign(t_core *shell, t_process *process)
{
	t_lst *lst;
	char *res;
	e_pstate id;

	id = P_WORD;
	if (!process->assign_list || !shell)
		return ;
	res = NULL;
	lst = process->assign_list;
	while (lst)
	{
		id = find_expansion(((t_db*)lst->content)->value);
		printf("%s\n", ((t_db*)lst->content)->value);
		if ((res = do_expansion(shell, ((t_db*)lst->content)->value, id)))
		{
			ft_strdel(&((t_db*)lst->content)->value);
			((t_db*)lst->content)->value = ft_strdup(res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
}
