#include "sh42.h"

static const t_token    quotes[] =
{
	{P_DBPARENT_OPEN, "$((", 3},
	{P_PARENT_OPEN, "$(", 2},
	{P_BRACKET_OPEN, "${", 2},
	{P_DOLLAR, "$", 1},
	{P_TILDE, "~", 1},
	{P_EXP_INTERRUPT, NULL, 0}
};

// {P_DBPARENT_CLOSE, "))", 2},
	// {P_PARENT_CLOSE, ")", 1},
	// {P_BRACKET_CLOSE, "}", 1},

	// else if (id = P_DBPARENT_CLOSE)
	// else if (id = P_PARENT_OPEN)
	// else if (id = P_PARENT_CLOSE)
	// else if (id = P_BRACKET_CLOSE)
	// else if (id = P_BRACKET_CLOSE)
	// else if (id = P_TILDE)


int exp_dbparen(t_lexer *lexer, e_parser_state id, int len)
{
	char *str;
	int index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "$((", len))
	{
		index = lexer->buf_pos;
		while (ft_strncmp(&lexer->buff[index], "))", 2))
			index++;
		index += 2;
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, index - lexer->buf_pos)))
			return (0);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, id, str), sizeof(t_token)))))
			return (0);
		init_token(&lexer->token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (index);
}

int exp_paren(t_lexer *lexer, e_parser_state id, int len)
{
	char *str;
	int index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "$(", len))
	{
		index = lexer->buf_pos;
		while (ft_strncmp(&lexer->buff[index], ")", 1))
			index++;
		index++;
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, index - lexer->buf_pos)))
			return (0);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, id, str), sizeof(t_token)))))
			return (0);
		init_token(&lexer->token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (index);
}

int exp_bracket(t_lexer *lexer, e_parser_state id, int len)
{
	char *str;
	int index;

	index = 0;
	str = NULL;
	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "${", len))
	{
		index = lexer->buf_pos;
		while (ft_strncmp(&lexer->buff[index], "}", 1))
			index++;
		index++;
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, index - lexer->buf_pos)))
			return (0);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, id, str), sizeof(t_token)))))
			return (0);
		init_token(&lexer->token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (index);
}

int exp_dollar(t_lexer *lexer, e_parser_state id, int len)
{
	char *str;
	int index;

	index = lexer->buf_pos + len;
	str = NULL;
	if (lexer->buff[lexer->buf_pos] == '$')
	{
		while ((lexer->buff[index]) && (lexer->buff[index] == '_' || ft_isdigit(lexer->buff[index]) || ft_isalpha(lexer->buff[index])))
			index++;
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, index - lexer->buf_pos)))
			return (0);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, id, str), sizeof(t_token)))))
			return (0);
		init_token(&lexer->token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (index);
}

int exp_tilde(t_lexer *lexer, e_parser_state id, int len)
{
	char *str;

	str = NULL;
	if (lexer->buff[lexer->buf_pos] == '~')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len)))
			return (0);
		if (!(ft_lstappend(&lexer->tok, ft_lstnew(fetch_lexer_token(&lexer->token, id, str), sizeof(t_token)))))
			return (0);
		init_token(&lexer->token);
		free(str);
		lexer->ntok++;
		lexer->buf_pos += len;
	}
	return (len);
}

static int	create_expansions_token(t_lexer *lexer, e_parser_state id, int len)
{	
	int i;
	t_expansion expansions[] = {
								{exp_dbparen, P_DBPARENT_OPEN, 3},
								{exp_paren, P_PARENT_OPEN, 2},
								{exp_bracket, P_BRACKET_OPEN, 2},
								{exp_dollar, P_DOLLAR, 1},
								{exp_tilde, P_TILDE, 1},
								};

	i = 0;
	while (i < 5)
	{
		if (id == expansions[i].id && len == expansions[i].len)
		{
			if (expansions[i].func(lexer, id, expansions[i].len))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void		expansion_lexer(t_lexer *lexer)
{
	int 	i;

	i = 0;
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return ;
	}
	while (quotes[i].id != P_EXP_INTERRUPT)
	{
		if (!ft_strncmp(&lexer->buff[lexer->buf_pos], quotes[i].data, quotes[i].data_len))
		{
			// ft_printf("[%s] {%u   %s| %d} \n", &lexer->buff[lexer->buf_pos], quotes[i].id, quotes[i].data, i);
			if (create_expansions_token(lexer, quotes[i].id, quotes[i].data_len))
				break;
		}
		i++;
	}
	if (i == NB_OF_EXP)
		name_lexer(lexer);
}
