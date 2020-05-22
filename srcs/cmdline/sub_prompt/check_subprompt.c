/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subprompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:46:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 16:44:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static ssize_t	exit_subprompt_prio(t_core *shell, char *str)
{
	char		*saved;

	saved = ft_strdup(shell->term.buffer);
	ft_strdel(&shell->sub.keys);
	shell->sub.state = SP_END;
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_strdup(str);
	save_history(&shell->term);
	ft_strdel(&shell->term.buffer);
	ft_strdel(&str);
	shell->term.buffer = ft_strdup(saved);
	ft_strdel(&saved);
	return (0);
}

ssize_t			open_machine_subprompt(t_core *shell, t_subprompt *sub)
{
	char	*tmp;

	tmp = NULL;
	shell->term.sub_prompt = TRUE;
	ft_strdel(&shell->term.prompt);
	get_prompt_value(shell, "PS2");
	shell->term.status = CMD_SUBPROMPT;
	if (sub->keys)
		shell->term.buffer = ft_strjoinf(shell->term.buffer, NEW_LINE, 1);
	if (!sub->keys)
	{
		tmp = ft_strsub(shell->term.buffer, 0,
					ft_strlen(shell->term.buffer) - 1);
		sub->index--;
	}
	else
		tmp = ft_strdup(shell->term.buffer);
	subprompt_loader(shell);
	if (sub_prompt_error(&shell->term,
		(sub->keys) ? sub->keys[0] : '\0') == TRUE)
		return (exit_subprompt_prio(shell, tmp));
	shell->term.buffer = ft_strjoinf(tmp, shell->term.buffer, 3);
	sub->escaped = 0;
	return (0);
}

enum e_subp		start_subprompt(t_core *shell, t_subprompt *sub)
{
	if (!shell->term.buffer[sub->index])
		reboot_or_end_machine(shell, sub);
	else if (shell->term.buffer[sub->index] == '}'
		&& !sub->quoted && !sub->escaped && sub->keys && sub->keys[0] == '}')
		del_keys_subprompt_and_move(sub, '}');
	else if (sub->keys && sub->keys[0] == '\"' && sub->keys[1] == '}'
		&& shell->term.buffer[sub->index] == '\"'
		&& shell->term.buffer[sub->index + 1] == '}')
		del_keys_subprompt_and_move(sub, '\"');
	else if (shell->term.buffer[sub->index] == '\''
		&& !sub->escaped && !sub->dbquoted)
		sub->state = SP_QUOTE;
	else if (shell->term.buffer[sub->index] == '\"'
		&& !sub->escaped && !sub->quoted)
		sub->state = SP_DBQUOTE;
	else if (shell->term.buffer[sub->index] == '$' && !sub->quoted
		&& shell->term.buffer[sub->index + 1] == '{'
		&& shell->term.buffer[sub->index + 1])
		sub->state = SP_BRACEPARAM;
	else if (shell->term.buffer[sub->index] == '\\' && !sub->quoted)
		sub->state = SP_BACKSLASH;
	else
		sub->index++;
	sub->escaped = 0;
	return (sub->state);
}

static void		init_subprompt(t_subprompt *sub)
{
	sub->state = SP_START;
	sub->keys = NULL;
	sub->index = 0;
	sub->escaped = 0;
	sub->quoted = 0;
	sub->dbquoted = 0;
	sub->tu[SP_START] = start_subprompt;
	sub->tu[SP_DBQUOTE] = dbquote_subprompt;
	sub->tu[SP_QUOTE] = quote_subprompt;
	sub->tu[SP_BRACEPARAM] = braceparam_subprompt;
	sub->tu[SP_BACKSLASH] = backslash_subprompt;
	sub->tu[SP_END] = NULL;
}

ssize_t			check_subprompt(t_core *shell)
{
	if (!shell->term.buffer)
		return (FALSE);
	init_subprompt(&shell->sub);
	while (shell->sub.state != SP_END)
		shell->sub.state = shell->sub.tu[shell->sub.state](shell, &shell->sub);
	ft_strdel(&(shell->sub.keys));
	return (TRUE);
}
