#include "sh42.h"


t_lst	*expansion_lexer(t_lexer *lx, t_lst *lexer_token)
{
	e_estate		state;
	char *str;

	state = NB_EXPANSION_STATE;
	str = NULL;
	if (!lx->buff)
	{
		lx->status = L_END;
		return (lexer_token);
	}
	if ((state = find_expansion(&lx->buff[lx->buf_pos])) != NB_EXPANSION_STATE)
	{
		str = get_expansion(&lx->buff[lx->buf_pos], state);
		// ft_lstappend(&lexer_token, ft_lstnew(
					// fetch_token(&lx->token, state, str), sizeof(t_token)));
		lx->ntok++;
		lx->buf_pos += ft_strlen(str);
		ft_strdel(&str);
		return (lexer_token);
	}
	lx->status = L_START;
	return (lexer_token = word_lexer(lx, lexer_token));
}