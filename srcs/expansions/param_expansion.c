
#include "sh42.h"

char *exp_param(char *data, t_core *shell, t_expansion *expansion)
{
	printf("EXP_DOLLAR [%s %u]\n", data, expansion->type);
	t_db *db_tmp;
	char *tmp;
	int i;

	i = ft_strlen(data);
	tmp = NULL;
	db_tmp = NULL;
	if (expansion->type == P_BRACKET)
		tmp = ft_strsub(data, 2, i - 3);
	if (expansion->type == P_DOLLAR)
		tmp = ft_strsub(data, 1, i - 1);
	if (!(db_tmp = search_db(shell->env, tmp)))
	{
		free(data);
		free(tmp);
		return (data = ft_strnew(0));
	}
	else
	{
		free(tmp);
		free(data);
		return (data = ft_strdup(db_tmp->value));
	}
	return (data);
}
