#include "sh42.h"

int exp_dbparen_lexer(t_lexer *lexer, e_parser_state id, int len)
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

int exp_paren_lexer(t_lexer *lexer, e_parser_state id, int len)
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

int exp_bracket_lexer(t_lexer *lexer, e_parser_state id, int len)
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

int exp_dollar_lexer(t_lexer *lexer, e_parser_state id, int len)
{
	char *str;
	int index;

	index = lexer->buf_pos + len;
	str = NULL;
	(void)len;
	if (lexer->buff[lexer->buf_pos] == '$')
	{
		while (!ft_strchr(CHAR_INTERRUPT, lexer->buff[index]) && lexer->buff[index])
		{
			if (lexer->buff[index] == '_' || ft_isdigit(lexer->buff[index]) || ft_isalpha(lexer->buff[index]))
				index++;
			else
			{
				break;
				return (index);
			}
		}
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

int exp_tilde_lexer(t_lexer *lexer, e_parser_state id, int len)
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
