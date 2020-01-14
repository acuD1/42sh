#include "sh42.h"

char		*exp_get_tilde(char *string, int len)
{
	// char	*str;
	(void)string;
	(void)len;
	// str = NULL;
	// if (!ft_strncmp(string, "~", len))
	// {
	// 	// if (!(str = ft_strsub(string, string, len)))
	// 	// 	return (NULL);
	// 	// return (str);
	// }
	// return (string);
	return (ft_strdup("~"));
}

char		*exp_get_tildep(char *string, int len)
{
	// char	*str;
	(void)string;
	(void)len;
	// str = NULL;
	// if (!ft_strncmp(string, "~+", len))
	// {
	// 	if (!(str = ft_strsub(string, 0, len)))
	// 		return (NULL);
	// 	return (str)
	// }
	// return (string);
	return (ft_strdup("~+"));
}

char		*exp_get_tildem(char *string, int len)
{
	// char	*str;
	(void)string;
	(void)len;
	// str = NULL;
	// if (!ft_strncmp(string, "~-", len))
	// {
	// 	if (!(str = ft_strsub(string, 0, len)))
	// 		return (NULL);
	// 	return (str);
	// }
	// return (string);
	return (ft_strdup("~-"));
}