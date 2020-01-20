#include "sh42.h"

e_pstate get_quote_state(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (str[i + 1] && str[i + 1] == '\'')
				return (P_END);
			return (P_QUOTE);
		}
		if (str[i] == '\"')
		{
			if (str[i + 1] && str[i + 1] == '\"')
				return (P_END);
			return (P_DBQUOTE);
		}
		if (str[i] == '`')
		{
			if (str[i + 1] && str[i + 1] == '`')
				return (P_END);
			return (P_BQUOTE);
		}
	}
	return (P_END);
}

char *quote_mechanisms(char *str)
{
	char *new;
	int i;
	int j;
	e_pstate state;

	j = 0;
	i = 0;
	new = NULL;
	state = 0;
	if (!str)
		return (NULL);
	i = ft_strlen(str);
	new = ft_strnew(i + 1);
	state = get_quote_state(str);
	i = 0;
	printf("%u\n", state);
	while (str[j])
	{
		if ((str[j] == '\"' && state == P_DBQUOTE)
			|| (str[j] == '`' && state == P_BQUOTE)
			|| (str[j] == '\'' && state == P_QUOTE))
			j++;
		new[i] = str[j];
		i++;
		j++;

	}
	if (new)
	{
		free(str);
		return (new);
	}
	printf("FINAL {%s] %d  ", new, j);
	return (str);
}

char *quote_removing(t_token *tok)
{
	if (!tok->data)
		return (NULL);
	// if (tok->id == P_DBQUOTE)
	// 	tok->data = point_de_cote(tok->data, '\"');
	// else if (tok->id == P_QUOTE)
	// 	tok->data = point_de_cote(tok->data, '\'');
	// else if (tok->id == P_BQUOTE)
	// 	tok->data = point_de_cote(tok->data, '`');

	return (tok->data);
}
