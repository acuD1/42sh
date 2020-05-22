/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_subpts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2020/05/08 00:23:32 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static u_int8_t		lex_n_parse(t_core *shell, t_lst *old, char *old_buffer)
{
	t_lst	*new;
	t_lst	*prev;

	new = NULL;
	prev = old;
	new = lexer(shell->term.buffer);
	shell->term.buffer = ft_strjoinf(old_buffer, shell->term.buffer, 3);
	if (parser(new) == FALSE)
	{
		ft_freetokenlist(&new);
		return (FALSE);
	}
	old = old->next;
	ft_strdel(&((t_token*)old->content)->data);
	free(((t_token*)old->content));
	free(old);
	prev->next = new;
	return (TRUE);
}

static u_int8_t		ouverture_du_subpts(t_core *shell, char *old_buffer)
{
	char			*saved;

	saved = NULL;
	set_termconfig(shell);
	subprompt_loader(shell);
	if (sub_prompt_error(&shell->term, '\0') == TRUE)
	{
		saved = ft_strdup(shell->term.buffer);
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(old_buffer);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
		ft_strdel(&old_buffer);
		shell->term.buffer = ft_strdup(saved);
		ft_strdel(&saved);
		shell->term.status = CMD_DONE;
		reset_config(shell);
		return (2);
	}
	check_subprompt(shell);
	reset_config(shell);
	return (0);
}

static u_int8_t		analyzer_subpts(t_core *shell, t_lst *old)
{
	char	*old_buffer;

	old_buffer = NULL;
	shell->term.sub_prompt = TRUE;
	ft_strdel(&shell->term.prompt);
	get_prompt_value(shell, "PS2");
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

static t_analyzer	*open_subpt(t_analyzer *anal, t_core *shell)
{
	u_int8_t	state;

	state = FALSE;
	while (state == FALSE)
	{
		if (shell->ctrl_c)
			return (exit_lpa(anal, shell));
		if ((state = analyzer_subpts(shell, anal->lexer)) == FALSE)
			continue ;
		else if (state == 2)
			return (exit_lpa(anal, shell));
		else
			break ;
	}
	return (anal);
}

t_analyzer			*add_process(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->process.type = ((t_token*)anal->lexer->content)->id;
	anal->state = A_SEPARATOR;
	anal = process_analyze(anal, shell);
	anal->process.command = fill_cmd_job(anal->lexer, anal->process.command);
	if (shell->is_interactive && anal->lexer->next
		&& ((t_token*)anal->lexer->next->content)->id == P_END)
		anal = open_subpt(anal, shell);
	return (anal);
}
