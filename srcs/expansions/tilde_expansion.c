#include "sh42.h"

char 	*exp_tilde(t_token *tok, t_core *shell, t_expansion *exp)
{
	t_db *db_tmp;
	char *path[] = {"HOME", "OLDPWD", "PWD"};
	int i;

	(void)exp;
	i = 0;
	db_tmp = NULL;
	if (!tok->data && !tok->data[0])
		return (NULL);
	if (tok->data[0] == '~' && tok->data[1] && tok->data[1] == '+')
		i = 2;
	else if (tok->data[0] == '~' && tok->data[1] && tok->data[1] == '-')
		i = 1;
	else if (tok->data[0] == '~')
		i = 0;
	if ((db_tmp = search_db(shell->env, path[i])))
		return (ft_strdup(db_tmp->value));
	return (NULL);
}
