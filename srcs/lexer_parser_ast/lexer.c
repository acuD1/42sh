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

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

void ft_init_lex(t_lexer *lexer)
{
	lexer->lex[START] = start_lexer;
	// lexer->lex[NAME] = name_lexer;
	// lexer->lex[IO_NUMBER] = number_lexer;
	// lexer->lex[NEWLINE] = newline_lexer;
	// lexer->lex[ASSIGNEMENT_WORD] = assignement_word_lexer;
	// lexer->lex[END] = end_lexer;
}

t_lexer *init_lexer(t_core *shell, char *line)
{
	t_lexer *new;

	if (!line || !shell)
		return (NULL);
	if (!(new = (t_lexer*)malloc(sizeof(t_lexer))))
		return (NULL);
	new->buff = line;
	new->status = START;
	new->ntok = 0;
	new->szbuff = ft_strlen(line);
	new->tok = NULL;
	// new->tok = (t_lst*)malloc(sizeof(t_lst));
	// new->tok->prev = NULL;
	// new->tok->next = NULL;
	ft_init_lex(new);
	return (new);
}

// enum nodetype add_tok_type(char *name)
// {

// }

// void end_lexer(t_lexer *lexer);
// void name_lexer(t_lexer *lexer);
// void number_lexer(t_lexer *lexer);
// void assignement_word_lexer(t_lexer *lexer);


void start_lexer(t_lexer *lexer)
{
	if (*lexer->buff == '\0')
		lexer->status = END;
	else if (*lexer->buff == ' ' || *lexer->buff == '\t')
	{
		while (*lexer->buff == ' ' || *lexer->buff == '\t')
			lexer->buff++;
	}
	else if (*lexer->buff == '\n')
		lexer->status = NEWLINE;
	else if (ft_isdigit(*lexer->buff))
		lexer->status = IO_NUMBER;
	else
		lexer->status = NAME;
	printf("%u\n", lexer->status);
}

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
	// tok->type = add_tok_type(name); 
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

void ft_printtoklist(t_lexer *lexer)
{
	t_token *tmp;

	tmp = NULL;
	if (!lexer->tok)
		return;
	printf("list avec %zu node \nAc en data        '%s'  '%u'\n", lexer->ntok, lexer->buff, lexer->status);
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

	// if (line == NULL)
	// 	return ;
	// while (*line == '\t' || *line == ' ')
	// 	line++;
	// if (*line == '\0')
		// return ;
	lexer = init_lexer(shell, line);
	// while (lexer->status != END)
		lexer->lex[lexer->status](lexer);
		// tokenizator(lexer, line); // envoyer line par line a une fct qui va la parcourir et creer une list de token en consequence
	//parser = parser(lexer, shell);// while (lexer->tok->type != EOF) -> PARSER
	//shell.ast = ast(parser);// ptr sur fct qui prend lchar par char et cree les token jusqua EOF et/ou !line
}