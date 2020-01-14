/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:18 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:19 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char *point_de_cote(char *src, char quote)
{
	char *one;
	char *two;
	char *three;
	char *vivalagerie;
	int nb[3];

	nb[0] = 0;
	nb[1] = ft_strlen(src);
	nb[2] = nb[1] + 1;
	one = NULL;
	two = NULL;
	three = NULL;
	vivalagerie = NULL;
	if (src[0] == quote && src[nb[1] - 1] == quote)
	{

		one = ft_strsub(src, 1, nb[1] - 2);
		free(src);
		return (one);
	}
	if (src[0] != quote)
	{
		while (src[nb[0]] != quote)
			nb[0]++;
		one = ft_strsub(src, 0, nb[0]);
		printf("one %s\n", one);
	}
	if (src[--nb[1]] != quote)
	{
		while (src[nb[1]] != quote)
			nb[1]--;
		two = ft_strsub(src, nb[1] + 1, nb[2] - nb[1]);
		printf("two %s\n", two);
	}
	if (!one)
	{
		one = ft_strsub(src, 1, ft_strlen(two));
		printf("1 %s\n", one);
	}
	if (!two)
	{
		two = ft_strsub(src, ft_strlen(one), ft_strlen(src) - 1);
		printf("2 %s\n", two);
	}
	if (one && two)
	{
		nb[2] = (ft_strlen(src)) - (ft_strlen(one) + ft_strlen(two) + 2);
		three = ft_strsub(src, ft_strlen(one) + 1, nb[2]);
		// three = ft_strjoinf(one, two, 4);
		printf("3 %s nb[2] %d\n", three, nb[2]);
		free(src);
		return (three);
	}

	// three = ft_strsub(src, ft_strlen(one), ft_strlen(src) - (ft_strlen(one) + ft_strlen(two)));
	// printf("%s %s\n", one, two);
	// nb[2] = ft_strlen(src) - (ft_strlen(one) + ft_strlen(two) + 2);
	// nb[0] = ft_strlen(one) + 1;
	// printf("start %d size %d\n", nb[0], nb[1]);
	// three = ft_strsub(src, nb[0], nb[1]);
	// printf("3 '%s'\n", three);
	// vivalagerie = ft_strjoinf(one, three, 4);
	// one = ft_strjoinf(vivalagerie, two, 4);
		// return (one);
	// if (src[nb[1] - 1] != quote)
	// {
	// 	while (src[nb[1]] != quote)
	// 		nb[1]--;
	// 	three = ft_strsub(src, nb[1], nb[2] - nb[1]);
	// }
	// two = ft_strsub(src, nb[0], nb[2] - (nb[1] + nb[0]));
	// printf("{%s}+{%s}+{%s}      %d %d %d\n", one, two, three, nb[0], nb[1], nb[2]);
	// one = ft_strjoinf(one, two, 4);
	// two = ft_strjoinf(three, one, 4);
	// free(src);
	// // printf("NUMBER 2 %s\n", two);
	// return (two);
	return (src);
}

char *quote_removing(t_token *tok)
{
	if (!tok->data)
		return (NULL);
	if (tok->id == P_DBQUOTE)
		tok->data = point_de_cote(tok->data, '\"');
	else if (tok->id == P_QUOTE)
		tok->data = point_de_cote(tok->data, '\'');
	else if (tok->id == P_BQUOTE)
		tok->data = point_de_cote(tok->data, '`');
	return (tok->data);
}

static char	**create_tablo(char *str)
{
	char	**tablo;

	if (!str)
		return (NULL);
	tablo = NULL;
	if (!(tablo = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	tablo[0] = ft_strdup(str);
	tablo[1] = NULL;
	return (tablo);
}

char		**ft_add_arg_cmd_process(char **tablo, char *str)
{
	char	**tb;
	int		j;

	j = 0;
	tb = NULL;
	if (!str)
		return (NULL);
	if (!tablo)
		return (tablo = create_tablo(str));
	if (!(tb = (char**)malloc(sizeof(char*) * (ft_tablen(tablo) + 2))))
		return (NULL);
	while (tablo[j])
	{
		tb[j] = ft_strdup(tablo[j]);
		free(tablo[j]);
		j++;
	}
	tb[j] = ft_strdup(str);
	tb[j + 1] = NULL;
	free(tablo);
	return (tb);
}

char		*fill_cmd_job(t_lst *tok_lst, char *cmd, int flag)
{
	char	*str;
	t_token *token;

	str = NULL;
	if (!tok_lst || !tok_lst->content)
		return (NULL);
	token = (t_token*)tok_lst->content;
	if ((tok_lst->next && ((t_token*)tok_lst->next->content)->id == 32)
		|| token->id == 0 || !flag)
		str = ft_strdup(token->data);
	else
		str = ft_strjoin(token->data, " ");
	cmd = ft_strjoinf(cmd, str, 4);
	return (cmd);
}