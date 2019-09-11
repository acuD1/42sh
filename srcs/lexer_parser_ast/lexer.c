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

// void tokenizator(t_lexer *lexer, char *line)
// {
// 	char **tab;
// 	int i;


// 	i = 0;
// 	//rajouter la fct qui prend chr par char et fait des token
// 	if (!(tab = ft_strsplit(line, " \t")))
// 		return ;
// 	while (tab[i])
// 	{
// 		printf("%s %zu\n", tab[i], ft_strlen(tab[i]));
// 		ft_add_token(tab[i], &lexer->tok);
// 		lexer->ntok++;
// 		i++;
// 	}
// 	ft_printtoklist(lexer);
// }

/*
**	TO DO:
*/

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
	while (lexer->status != END)
		lexer->lex[lexer->status](lexer);
	ft_printtoklist(lexer);

		// tokenizator(lexer, line); // envoyer line par line a une fct qui va la parcourir et creer une list de token en consequence
	//parser = parser(lexer, shell);// while (lexer->tok->type != EOF) -> PARSER
	//shell.ast = ast(parser);// ptr sur fct qui prend lchar par char et cree les token jusqua EOF et/ou !line
}