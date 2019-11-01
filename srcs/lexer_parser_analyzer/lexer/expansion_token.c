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

static int	create_expansions_token(t_lexer *lexer, e_parser_state id)
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
			if ((expansions[i].func(lexer, id, expansions[i].len)))
				return (1);
			else
				word_lexer(lexer);
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
			if (create_expansions_token(lexer, quotes[i].id))
				return;
		}
		i++;
	}
}
