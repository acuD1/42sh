/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:41:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/07/31 15:43:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lst	*ft_create_token(char *name)
{
	t_lst *new;
	t_token *tok;

	tok = NULL;
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	tok->id = ft_strdup(name);
	tok->type = NODE_NULL; 
	new->content = (char*)tok;
	return (new);
}

t_lst	*ft_add_token(char *name, t_lst **curr)
{
	t_lst		*tmp;
	t_lst		*new;

	if (!(*curr))
		return (*curr = ft_create_token(name));
	if ((*curr)->next)
	{
		new = (*curr);
		while (new->next)
			new = new->next;
		tmp = ft_create_token(name);
		tmp->prev = new;
		tmp->next = NULL;
		new->next = tmp;
	}
	else
	{
		tmp = *curr;
		tmp->next = ft_create_token(name);
		tmp->next->prev = tmp;
	}
	return (*curr);
}

t_lexer *init_lexer(t_core *shell, char *line)
{
	t_lexer *new;

	if (!line || !shell)
		return (NULL);
	if (!(new = (t_lexer*)malloc(sizeof(t_lexer))))
		return (NULL);
	new->buff = line;
	new->status = 1;
	new->ntok = 0;
	new->szbuff = ft_strlen(line);
	new->tok = NULL;
	// new->tok = (t_lst*)malloc(sizeof(t_lst));
	// new->tok->prev = NULL;
	// new->tok->next = NULL;
	return (new);
}

void ft_printtoklist(t_lexer *lexer)
{
	t_token *tmp;

	tmp = NULL;
	if (!lexer->tok)
		return;
	printf("list avec %zu node \nAc en data        '%s'\n", lexer->ntok, lexer->buff);
	while (lexer->tok->next)
	{
		tmp = (t_token*)lexer->tok->content;
		printf("%s\n", tmp->id);
		lexer->tok = lexer->tok->next;
	}
	while (lexer->tok)
	{
		tmp = (t_token*)lexer->tok->content;
		printf("%s\n", tmp->id);
		lexer->tok = lexer->tok->prev;
	}
}

void tokenizator(t_lexer *lexer, char *line)
{
	char **tab;
	int i;


	i = 0;
	if (!(tab = ft_strsplit(line, " \t")))
		return ;
	while (tab[i])
	{
		printf("%s %zu\n", tab[i], ft_strlen(tab[i]));
		ft_add_token(tab[i], &lexer->tok);
		lexer->ntok++;
		i++;
	}
	ft_printtoklist(lexer);
}

void	lexer(t_core *shell, char *line)
{
	t_lexer *lexer;
	// t_parser *parser;

	if (line == NULL)
		return ;
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return ;
	lexer = init_lexer(shell, line);
	tokenizator(lexer, line); // envoyer line par line a une fct qui va la parcourir et creer une list de token en consequence
	//parser = parser(lexer, shell);// while (lexer->tok->type != EOF) -> PARSER
	//shell.ast = ast(parser);// ptr sur fct qui prend lchar par char et cree les token jusqua EOF et/ou !line
}