#include "sh42.h"

t_lst *exp_dbparen_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
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
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (lexer_token);
}

t_lst *exp_paren_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
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
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (lexer_token);
}

t_lst *exp_bracket_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
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
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (lexer_token);
}

t_lst *exp_dollar_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
{
	char *str;
	int index;

	index = lexer->buf_pos + len;
	str = NULL;
	(void)len;
	if (lexer->buff[lexer->buf_pos] == '$')
	{
		while (lexer->buff[index] == '_' || ft_isdigit(lexer->buff[index]) || ft_isalpha(lexer->buff[index]))
				index++;
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, index - lexer->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos = index;
	}
	return (lexer_token);
}

t_lst *exp_tilde_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
{
	char *str;

	str = NULL;
	if (lexer->buff[lexer->buf_pos] == '~')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos += len;
	}
	return (lexer_token);
}
