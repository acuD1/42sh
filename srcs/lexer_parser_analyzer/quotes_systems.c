#include "sh42.h"

e_pstate get_quote_state(char *str)
{

	// if (str)
	// int i;

	// i = -1;
	// while (str[++i])
	// {
	// 	if (str[i] == '\'')
	// 	{
	// 		if (str[i + 1] && str[i + 1] == '\'')
	// 			return (P_END);
	// 		return (P_QUOTE);
	// 	}
	// 	if (str[i] == '\"')
	// 	{
	// 		if (str[i + 1] && str[i + 1] == '\"')
	// 			return (P_END);
	// 		return (P_DBQUOTE);
	// 	}
	// 	if (str[i] == '`')
	// 	{
	// 		if (str[i + 1] && str[i + 1] == '`')
	// 			return (P_END);
	// 		return (P_BQUOTE);
	// 	}
	// }
	(void)str;
	return (P_END);
}

char *quote_removing(char *str)
{
	e_pstate state;
	int i;
	char *new;

	i = 0;
	state = 0;
	new = NULL;
	if (!str)
		return (NULL);
	return (str);
}
	// new = ft_strnew()
	// while (str[i])
	// {
	// 	if (str[i] == '\'')
	// 	{
	// 		state = P_QUOTE;

	// 	}
	// }
// 	if (state == P_DBQUOTE)
// 		str = point_de_cote(str, '\"');
// 	else if (state == P_QUOTE)
// 		str = point_de_cote(str, '\'');
// 	else if (state == P_BQUOTE)
// 		str = point_de_cote(str, '`');
// 	return (str);
// }
