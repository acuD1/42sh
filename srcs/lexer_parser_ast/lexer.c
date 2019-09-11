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
	lexer->lex[OPERATOR] = operator_lexer;
	lexer->lex[NAME] = name_lexer;
	lexer->lex[IO_NUMBER] = number_lexer;
	lexer->lex[NEWLINE] = newline_lexer;
	lexer->lex[ASSIGNEMENT_WORD] = assignement_word_lexer;
	lexer->lex[END] = end_lexer;
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
	new->buf_pos = 0;
	new->szbuff = ft_strlen(line);
	new->tok = NULL;
	new->io_here = 0;
	// new->tok = (t_lst*)malloc(sizeof(t_lst));
	// new->tok->prev = NULL;
	// new->tok->next = NULL;
	ft_init_lex(new);
	return (new);
}

static void	*token_set(t_token *token, e_tokenid opeid, char *data)
{
  if (token->id == TOK_WORD)
    free(token->data);
  token->id = opeid;
  token->data = data;
  if (data)
  	token->data_len = ft_strlen(data);
  else
  	token->data_len = 0;
  return (token);
}

void end_lexer(t_lexer *lexer)
{
	// printf("END %u\n", lexer->status);
	if (lexer->buff == '\0')
		lexer->status = END;
	else
	{
		lexer->status = START;
		lexer->buf_pos++;
	}
}

void name_lexer(t_lexer *lexer)
{
	int i;

	i = 0;
	if (lexer->buff[lexer->buf_pos])
	{
		i = lexer->buf_pos;
		while (lexer->buff[i] != ' ' || lexer->buff[i] != '\t')
			i++;
		// ft_add_token(&lexer->tok, TOK_WORD, ft_strsub(lexer->buff, lexer->buf_pos, i));
		lexer->buf_pos += i + 1;
	}
	// ft_add_token(lexer->buff, &lexer->tok);
	lexer->ntok++;
	// printf("NAME %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = NAME;
	lexer->status = START;
}

void number_lexer(t_lexer *lexer)
{
	// ft_add_token(lexer->buff, &lexer->tok);
	// lexer->ntok++;
	// lexer->buff++;
	// printf("Nbr %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = IO_NUMBER;
	lexer->status = START;
}

void newline_lexer(t_lexer *lexer)
{
	// ft_add_token(lexer->buff, &lexer->tok);
	// lexer->ntok++;
	// printf("NwlinE %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = NEWLINE;
	lexer->status = START;
}
//(const char *buf, size_t *buf_pos, s_token *token)
void operator_lexer(t_lexer *lexer)
{
	static t_token    ope[] =
	  {
	    {TOK_NEWLINE, "\n", 1},
	    {TOK_ANDIF , "&&", 2},
	    {TOK_AND, "&", 1},
	    {TOK_ORIF, "||", 2},
	    {TOK_PIPE, "|", 1},
	    {TOK_DSEMI, ";;", 2},
	    {TOK_SEMICOLON, ";", 1},
	    {TOK_DLESSDASH, "<<-", 3},
	    {TOK_DLESS, "<<", 2},
	    {TOK_LESSGREAT, "<>", 2},
	    {TOK_LESSAND, "<&", 2},
	    {TOK_LESS, "<", 1},
	    {TOK_DGREAT, ">>", 2},
	    {TOK_GREATAND, ">&", 2},
	    {TOK_CLOBBER, ">|", 2},
	    {TOK_GREAT, ">", 1},
	    {TOK_PARENT_OPEN, "(", 1},
	    {TOK_PARENT_CLOSE, ")", 1},
	    {TOKEN, NULL, 0}
	  };
	int i;

	i = 0;
	while (ope[i].id != TOKEN)
	{
		if (!strncmp(lexer->buff, ope[i].data, ope[i].data_len))
		{
			    if (lexer->buf_pos)
					lexer->buf_pos += ope[i].data_len;
     			if (lexer->tok)
					token_set(lexer->tok->content, ope[i].id, ope[i].data);
				// printf("%u %s \n", ((t_token*)lexer->tok->content)->id, ((t_token*)lexer->tok->content)->data);
				printf("%s\n", ope[i].data);
      	}
      	i++;
	}
	lexer->status = START;
}

void assignement_word_lexer(t_lexer *lexer)
{
	// ft_add_token(lexer->buff, &lexer->tok);
	// lexer->ntok++;
	// printf("assi namE %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = ASSIGNEMENT_WORD;
	lexer->status = START;
}



void start_lexer(t_lexer *lexer)
{
	printf("%c\n",lexer->buff[lexer->buf_pos] );
	if (lexer->buff[lexer->buf_pos] == '\0')
		lexer->status = END;
	else if (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
	{
		lexer->io_here = 0;
		while (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
			lexer->buf_pos++;
	}
	// else if (ft_isdigit(lexer->buff[buf_pos]))
		// lexer->status = IO_NUMBER;
	else if (ft_strchr(OPERATORS, lexer->buff[lexer->buf_pos]))
	{
		lexer->status = OPERATOR;
	}
	// else if (ft_strchr(CHAR_INTERRUPT, lexer->buff[buf_pos]))
		// lexer->status = NEWLINE;
	// else if (ft_strchr("=", lexer->buff[buf_pos])) // contien un signe = a la fin
		// lexer->status = ASSIGNEMENT_WORD;
	else
		lexer->status = NAME;
	printf("statu %u\n", lexer->status);
	lexer->buf_pos++;
	// lexer->status = END;
}

t_lst	*ft_create_token(char *data, e_tokenid opeid)
{
	t_lst *new;
	t_token *tok;

	tok = NULL;
	printf("TOK %s\n",data );
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new->content = token_set(tok, opeid, data);
	return (new);
}

t_lst	*ft_add_token(t_lst **curr, e_tokenid opeid, char *data)
{
	t_lst		*tmp;
	t_lst		*new;

	if (!(*curr))
		return (*curr = ft_create_token(data, opeid));
	if ((*curr)->next)
	{
		new = (*curr);
		while (new->next)
			new = new->next;
		tmp = ft_create_token(data, opeid);
		tmp->prev = new;
		tmp->next = NULL;
		new->next = tmp;
	}
	else
	{
		tmp = *curr;
		tmp->next = ft_create_token(data, opeid);
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
		printf("%s\n", tmp->data);
		lexer->tok = lexer->tok->next;
	}
	while (lexer->tok)
	{
		tmp = (t_token*)lexer->tok->content;
		printf("%s\n", tmp->data);
		lexer->tok = lexer->tok->prev;
	}
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