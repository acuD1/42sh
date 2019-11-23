#include "sh42.h"

char 	*exp_tilde(char *data, t_core *shell)
{
	t_db *db_tmp;
	char *path[] = {NULL, "HOME", "OLDPWD", "PWD"};
	int i;

	i = 0;
	db_tmp = NULL;
	if (!data && !data[0])
		return (NULL);
	if (data[0] == '~' && data[1] && data[1] == '+')
		i = 3;
	else if (data[0] == '~' && data[1] && data[1] == '-')
		i = 2;
	else if (data[0] == '~')
		i = 1;
	if (!(db_tmp = search_db(shell->env, path[i])))
	{
		free(data);
		return (data = ft_strnew(0));
	}
	else
	{
		free(data);
		return (data = ft_strdup(db_tmp->value));
	}
	return (NULL);
}
