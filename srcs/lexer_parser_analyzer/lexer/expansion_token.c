#include "sh42.h"

static const t_token    quotes[] =
{
	{P_TILDE, "~", 1},
	{P_DBPARENT, "$((", 3},
	{P_PARENT, "$(", 2},
	{P_BRACKET, "${", 2},
	{P_HOOK, "$[", 2},
	{P_DOLLAR, "$", 1},
	{P_EXP_INTERRUPT, NULL, 0}
};

t_lst *exp_hook_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token)
{
	char *str;
	int index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "$[", len))
	{
		index = lexer->buf_pos;
		while (&lexer->buff[index])
		{
			if (lexer->buff[index] == ']')
			{
				break; // CECI EST UN BUG
			}
			else
				index++;
			if (!lexer->buff[index + 1])
			{
				ft_dprintf(2, "mathsubst>\n" );
				// lexer->buf_pos = index;
				break;
				// subprompt("braceparam>");
			}
		}
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

static t_lst	*create_expansions_token(t_lexer *lexer, e_parser_state id, t_lst *lexer_token)
{	
	int i;
	t_expansion expansions[] = {
								{exp_tilde_lexer, P_TILDE, 1},
								{exp_dbparen_lexer, P_DBPARENT, 3},
								{exp_paren_lexer, P_PARENT, 2},
								{exp_bracket_lexer, P_BRACKET, 2},
								{exp_hook_lexer, P_HOOK, 2},
								{exp_dollar_lexer, P_DOLLAR, 1},
								};

	i = 0;
	while (i < NB_OF_EXP)
	{
		if (id == expansions[i].id)
		{
			if ((lexer_token = expansions[i].func(lexer, id, expansions[i].len, lexer_token)))
				return (lexer_token);
			// else
				// lexer_token = word_lexer(lexer, lexer_token);
		}
		i++;
	}
	return (lexer_token);
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
			if ((lexer_token = create_expansions_token(lexer, quotes[i].id, lexer_token)))
				return (lexer_token);
		}
		i++;
	}
	if (i == NB_OF_EXP)
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return(lexer_token);
}
