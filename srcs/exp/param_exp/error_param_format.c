#include "sh42.h"

char *error_moar_format_third(char **tablo, char *data)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s: %s erreur de syntaxe dans l'expression (le symbole erroné est « %s »)\n", tablo[0], data, data);
	ft_tabfree(tablo);
	return (NULL);
}

char *error_moar_format_bis(char *data)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s erreur de syntaxe dans l'expression (le symbole erroné est « : »)\n", data);
	return (NULL);
}
char *error_moar_format_param(char **tablo, char *data)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s erreur de syntaxe dans l'expression (le symbole erroné est « %s »)\n",
		data, &data[ft_strlen(tablo[0]) + ft_strlen(tablo[1]) + ft_strlen(tablo[2]) + 2]);
	ft_tabfree(tablo);
	return (NULL);
}