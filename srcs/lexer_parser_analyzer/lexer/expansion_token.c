#include "sh42.h"

static const t_token    quotes[] =
{
	{P_TILDE, "~", 1},
	{P_DBPARENT, "$((", 3},
	{P_PARENT, "$(", 2},
	{P_BRACKET, "${", 2},
	{P_DOLLAR, "$", 1},
	{P_EXP_INTERRUPT, NULL, 0}
};

static int	create_expansions_token(t_lexer *lexer, e_parser_state id, t_lst *lexer_token)
{	
	int i;
	t_expansion expansions[] = {
								{exp_tilde_lexer, P_TILDE, 1},
								{exp_dbparen_lexer, P_DBPARENT, 3},
								{exp_paren_lexer, P_PARENT, 2},
								{exp_bracket_lexer, P_BRACKET, 2},
								{exp_dollar_lexer, P_DOLLAR, 1},
								};

	i = 0;
	while (i < 5)
	{
		if (id == expansions[i].id)
		{
			if ((expansions[i].func(lexer, id, expansions[i].len, lexer_token)))
				return (1);
			else
				lexer_token = word_lexer(lexer, lexer_token);
		}
		i++;
	}
	return (0);
}

t_lst		*expansion_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int 	i;

	i = 0;
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return(lexer_token);
	}
	while (quotes[i].id != P_EXP_INTERRUPT)
	{
		if (!ft_strncmp(&lexer->buff[lexer->buf_pos], quotes[i].data, quotes[i].data_len))
		{
			if (create_expansions_token(lexer, quotes[i].id, lexer_token))
				return (lexer_token);
		}
		i++;
	}
	if (i == NB_OF_EXP)
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return(lexer_token);
}
