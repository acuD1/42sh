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
		while ((str[j] == '\"' )
			|| (str[j] == '`' )
			|| (str[j] == '\'' ))
			j++;
		new[i] = str[j];
		i++;
		j++;

	}
	if (new)
	{
		free(str);
		return (ft_strdup(new));
	}
	printf("FINAL {%s] %d  ", new, j);
	return (str);
}

char *quote_removing(char *str)
{
	e_pstate state;

	state = 0;
	if (!str)
		return (NULL);
	state = get_quote_state(str);
	if (state == P_DBQUOTE)
		str = point_de_cote(str, '\"');
	else if (state == P_QUOTE)
		str = point_de_cote(str, '\'');
	else if (state == P_BQUOTE)
		str = point_de_cote(str, '`');
	return (str);
}
