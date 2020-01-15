#include "sh42.h"

int ft_find_first_char(char *s, char quote)
{
	int i;
	char *str;

	i = 0;
	str = s;
	while (str[i++])
	{
		if (str[i] == quote)
			break ;
	}
	return (i);
}

char *begin_wquote(char *src, char quote)
{
	char *one;
	char *two;
	int i;
	int len;

	i = 1;
	len = ft_strlen(src);
	one = NULL;
	two = NULL;
	if (src && src[0] == quote && src[i] != quote)
	{
		i = ft_find_first_char(&src[1], quote);
		one = ft_strsub(src, 1, i);
		if (src[i + 1] && i < len)
			two = ft_strsub(src, i + 2, len - i);
		return (ft_strjoinf(one,two, 4));
	}
	return (src);
}

char *end_wquote(char *src, char quote)
{
	char *one;
	char *two;
	int i;
	int len;

	len = ft_strlen(src) - 1;
	i = 0;
	one = NULL;
	two = NULL;
	if (src && src[len] == quote && src[len - 1] != quote)
	{
		i = ft_find_first_char(src, quote);
		one = ft_strsub(src, 0, i);
		if (src[i + 1] && i < len)
			two = ft_strsub(src, i + 1, len - i - 1);
		return (ft_strjoinf(one,two, 4));
	}
	return (src);
}

char *unquote_me_bb(char *src, char quote)
{
	int i;
	char *one;
	char *two;
	char *three;

	i = 0;
	one = NULL;
	two = NULL;
	three = NULL;
	i = ft_find_first_char(src, quote);
	one = ft_strsub(src, 0, i);
	i = ft_strlen(src) - 1;
	if (src[i] != quote)
		while (src[i] != quote)
			i--;
	two = ft_strsub(src, i + 1, ft_strlen(src) - i);
	if (one && two)
	{
		i = (ft_strlen(src)) - (ft_strlen(one) + ft_strlen(two) + 2);
		three = ft_strsub(src, ft_strlen(one) + 1, i);
		one = ft_strjoinf(one, three, 4);
		three = ft_strjoinf(one, two, 4);
		return (three);
	}
	return (src);
}

char *point_de_cote(char *src, char quote)
{
	char *unquoted;
	int len;

	unquoted = NULL;
	len = ft_strlen(src);
	if (src[0] == quote && src[len - 1] == quote)
		unquoted = ft_strsub(src, 1, len - 2);
	else if (src[0] == quote && src[len - 1] != quote)
		unquoted = begin_wquote(src, quote);
	else if (src[0] != quote && src[len - 1] == quote)
		unquoted = end_wquote(src, quote);
	else
		unquoted = unquote_me_bb(src, quote);
	free(src);
	return (unquoted);
}
