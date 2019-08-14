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

// t_lexage *init_lexage()
// {
// 	static t_lexage *lexage[] ={
// 		;
// 							{"cd", ft_cd},
// 							{"exit", ft_exit},
// 							{"env", ft_env},
// 							{"setenv", ft_setenv},
// 							{"unsetenv", ft_unsetenv},
// 							{"echo", ft_echo}};

// }


t_token	*ft_create_token(char *name)
{
	t_token *new;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->id = ft_strdup(name);
	new->type = NODE_NULL; 
	return (new);
}

t_token	*ft_add_token(char *name, t_token **curr)
{
	t_token		*tmp;
	t_token		*new;

	if (!(*curr))
	{
		return (*curr = ft_create_token(name));
	}
	if ((*curr)->next)
	{
		new = (*curr);
		while (new && new->next)
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
	new->tok = (t_token*)malloc(sizeof(t_token));
	// new->tok->next = NULL;
	// new->tok->prev = NULL;
	// new->tok->id = NULL;
	// new->tok->type = NODE_NULL;
	// lexer->lexatisation = init_lexage();
	// lexer->lexatisation = NULL;
	return (new);
}

// t_token *create_token(enum nodetype type, char *data, t_lexer *lexer)
// {
// 	ft_lstappend(&lexer->tok, ft_lstnew(line, ft_strlen(line)));

// }

void ft_printtoklist(t_lexer *lexer)
{
	if (!lexer->tok)
		return;
	printf("list avec %zu node \nAc en data        '%s'\n", lexer->ntok, lexer->buff);
	while (lexer->tok->next)
	{
		printf("%s\n", lexer->tok->id);
		lexer->tok = lexer->tok->next;
	}
	while (lexer->tok->prev)
	{
		printf("%s\n", lexer->tok->id);
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

// addtok
// print token
// ft_lstappend(&shell->env, ft_lstnew(fetch_db(&shell->db, environ[i]), sizeof(t_db)));

// int ft_isescaped(char c)
// {
// 	return ((c == '\a' || c == '\b' || c == '\f' || c == '\n' || c == '\r'
// 		|| c == '\t' || c == '\v') ? 1 : 0);
// }

void	lexer(t_core *shell, char *line)
{
	t_lexer *lexer;
	int	*pos[2]; //0 start 1 end
	int i;

	pos[0] = 0;
	pos[1] = 0;
	i = 0;


	if (line == NULL)
		return ;
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return ;
	lexer = init_lexer(shell, line);
	tokenizator(lexer, line);
	//envoyer line par line a une fct qui va la parcourir et creer une list de token en consequence
	// while (ft_isescaped(line[i])) //skip space
	// 	i++;
	// i = 0;
	// while (ft_iscomments(line[i])) //skip commentaire
		// i++;

	// while (lexer->tok->type != EOF)
	// {
	// 	//ptr sur fct qui prend lchar par char et cree les token jusqua EOF et/ou !line
	// 	if (!line[i])

	// }
}
 