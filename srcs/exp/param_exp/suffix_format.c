#include "sh42.h"

char *smallest_suffix_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;
	int		pattern_size;

	tablo = NULL;
	pattern_size = 0;
	tablo = ft_strsplit(data, "%");
	value = check_env_key(tablo[0], shell);
	pattern_size = ft_strlen(value) - ft_strlen(tablo[1]);
	if (ft_strequ(value + pattern_size, tablo[1]))
	{
		ft_tabfree(tablo);
		return (ft_strsub(value, 0, pattern_size));
	}
	else
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	return (NULL);
}

char *largest_suffix_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;

	tablo = NULL;
	tablo = ft_strsplit(data, "%");
	value = check_env_key(tablo[0], shell);
	printf("2 suffix key %s value %s\n", tablo[0], value);
	return (NULL);
}

char		*suffix_format(char *data, t_core *shell)
{
	//	x=file.c
	//	affiche du debut jusquau pattern si ca match sinn affiche tout
		//	echo ${x%.c} => file
			//	garde le plus petit pattern qui a match
		//	echo ${x%%.c} => file
			//	garde le plus grand pattern qui a match
	char *tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(data, '%')))
	{
		if (tmp[0] == '%')
		{
			if (tmp[1] == '%')
				return (largest_suffix_param(data, shell));
			else
				return (smallest_suffix_param(data, shell));
		}
	}
	return (NULL);
}
