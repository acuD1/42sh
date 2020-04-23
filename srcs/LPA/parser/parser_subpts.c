/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subpts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 15:48:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		add_lanouvellelistalasuite(t_lst *old, t_lst *new)
{
	t_lst *prev;

	prev = old;
	while (old)
	{
		old = old->next;
		if (((t_token*)old->content)->id == P_END)
			break ;
		prev = prev->next;
	}
	ft_strdel(&((t_token*)old->content)->data);
	free(((t_token*)old->content));
	free(old);
	prev->next = new;
}

static u_int8_t	lex_n_parse(t_core *shell, t_lst *old, char *old_buffer)
{
	t_lst	*new;

	new = NULL;
	new = lexer(shell->term.buffer);
	shell->term.buffer = ft_strjoinf(old_buffer, shell->term.buffer, 3);
	if (parser(new, shell) == FALSE)
	{
		ft_freetokenlist(&new);
		return (FALSE);
	}
	add_lanouvellelistalasuite(old, new);
	return (TRUE);
}

static u_int8_t	ouverture_du_subpts(t_core *shell, char *old_buffer)
{
	set_termconfig(shell);
	subprompt_loader(shell);
	if (sub_prompt_error(&shell->term, '\0') == TRUE)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(old_buffer);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
		ft_strdel(&old_buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
		shell->term.status = CMD_DONE;
		shell->subpts = 1;
		reset_config(shell);
		return (2);
	}
	check_subprompt(shell);
	reset_config(shell);
	return (0);
}

u_int8_t		parser_subpts(t_core *shell, t_lst *old)
{
	char	*old_buffer;

	old_buffer = NULL;
	shell->term.sub_prompt = TRUE;
	ft_strdel(&shell->term.prompt);
	get_prompt_value(shell, "PS2");
	shell->term.flag = FALSE;
	shell->term.status = CMD_SUBPROMPT;
	old_buffer = ft_strdup(shell->term.buffer);
	if (ouverture_du_subpts(shell, old_buffer) == 2)
		return (2);
	shell->term.status = CMD_DONE;
	shell->term.sub_prompt = FALSE;
	if (shell->term.buffer)
		return (lex_n_parse(shell, old, old_buffer));
	return (FALSE);
}

u_int8_t	graph(enum e_pstate *c, enum e_pstate n, enum e_pstate ps[])
{
	size_t	i;

	i = 0;
	if (ps == NULL)
		return (0);
	while (ps[i] != P_ERROR)
	{
		if (n == ps[i])
		{
			*c = n;
			return (1);
		}
		i++;
	}
	return (0);
}
