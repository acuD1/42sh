/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_analyzer_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:26:47 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:55:07 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_assign_analyze(t_anal analyze)
{
	analyze[A_ASSIGN][P_NEWLINE] = separator_analyze;
	analyze[A_ASSIGN][P_ANDIF] = separator_analyze;
	analyze[A_ASSIGN][P_AND] = separator_analyze;
	analyze[A_ASSIGN][P_ORIF] = separator_analyze;
	analyze[A_ASSIGN][P_PIPE] = separator_analyze;
	analyze[A_ASSIGN][P_SEMICOLON] = separator_analyze;
	analyze[A_ASSIGN][P_DLESSDASH] = redirect_analyze;
	analyze[A_ASSIGN][P_DLESS] = redirect_analyze;
	analyze[A_ASSIGN][P_LESS] = redirect_analyze;
	analyze[A_ASSIGN][P_DGREAT] = redirect_analyze;
	analyze[A_ASSIGN][P_GREATAND] = redirect_analyze;
	analyze[A_ASSIGN][P_GREAT] = redirect_analyze;
	analyze[A_ASSIGN][P_ASSIGN] = assign_analyze;
	analyze[A_ASSIGN][P_WORD] = cmd_analyze;
	analyze[A_ASSIGN][P_QUOTE] = cmd_analyze;
	analyze[A_ASSIGN][P_DBQUOTE] = cmd_analyze;
	analyze[A_ASSIGN][P_BQUOTE] = cmd_analyze;
	analyze[A_ASSIGN][P_ESCSEQ] = cmd_analyze;
	analyze[A_ASSIGN][P_DBPARENT] = cmd_analyze;
	analyze[A_ASSIGN][P_PARENT] = cmd_analyze;
	analyze[A_ASSIGN][P_HOOK] = cmd_analyze;
	analyze[A_ASSIGN][P_TILDE] = cmd_analyze;
	analyze[A_ASSIGN][P_TILDEM] = cmd_analyze;
	analyze[A_ASSIGN][P_TILDEP] = cmd_analyze;
	analyze[A_ASSIGN][P_END] = end_analyze;
}

void	init_ionumber_analyze(t_anal analyze)
{
	analyze[A_IONUMBER][P_DLESSDASH] = redirect_analyze;
	analyze[A_IONUMBER][P_DLESS] = redirect_analyze;
	analyze[A_IONUMBER][P_LESS] = redirect_analyze;
	analyze[A_IONUMBER][P_DGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_GREATAND] = redirect_analyze;
	analyze[A_IONUMBER][P_LESSAND] = redirect_analyze;
	analyze[A_IONUMBER][P_GREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_WORD] = cmd_analyze;
	analyze[A_IONUMBER][P_QUOTE] = cmd_analyze;
	analyze[A_IONUMBER][P_BQUOTE] = cmd_analyze;
	analyze[A_IONUMBER][P_DBQUOTE] = cmd_analyze;
	analyze[A_IONUMBER][P_ESCSEQ] = cmd_analyze;
	analyze[A_IONUMBER][P_END] = end_analyze;
}

void	init_redirect_analyze(t_anal analyze)
{
	analyze[A_REDIRECT][P_NEWLINE] = redirect_analyze;
	analyze[A_REDIRECT][P_PIPE] = separator_analyze;
	analyze[A_REDIRECT][P_SEMICOLON] = end_analyze;
	analyze[A_REDIRECT][P_DLESSDASH] = redirect_analyze;
	analyze[A_REDIRECT][P_DLESS] = redirect_analyze;
	analyze[A_REDIRECT][P_LESS] = redirect_analyze;
	analyze[A_REDIRECT][P_DGREAT] = redirect_analyze;
	analyze[A_REDIRECT][P_GREATAND] = redirect_analyze;
	analyze[A_REDIRECT][P_LESSAND] = redirect_analyze;
	analyze[A_REDIRECT][P_GREAT] = redirect_analyze;
	analyze[A_REDIRECT][P_IONUMBER] = ionbr_analyze;
	analyze[A_REDIRECT][P_ASSIGN] = assign_analyze;
	analyze[A_REDIRECT][P_WORD] = cmd_analyze;
	analyze[A_REDIRECT][P_BQUOTE] = cmd_analyze;
	analyze[A_REDIRECT][P_DBQUOTE] = cmd_analyze;
	analyze[A_REDIRECT][P_QUOTE] = cmd_analyze;
	analyze[A_REDIRECT][P_ESCSEQ] = cmd_analyze;
	analyze[A_REDIRECT][P_END] = end_analyze;
}

void	init_end_analyze(t_anal analyze)
{
	analyze[A_END][P_NEWLINE] = end_analyze;
	analyze[A_END][P_ANDIF] = separator_analyze;
	analyze[A_END][P_AND] = separator_analyze;
	analyze[A_END][P_PIPE] = redirect_analyze;
	analyze[A_END][P_ORIF] = separator_analyze;
	analyze[A_END][P_SEMICOLON] = separator_analyze;
	analyze[A_END][P_DLESSDASH] = redirect_analyze;
	analyze[A_END][P_DLESS] = redirect_analyze;
	analyze[A_END][P_LESS] = redirect_analyze;
	analyze[A_END][P_DGREAT] = redirect_analyze;
	analyze[A_END][P_GREATAND] = redirect_analyze;
	analyze[A_END][P_GREAT] = redirect_analyze;
	analyze[A_END][P_WORD] = cmd_analyze;
	analyze[A_END][P_DBQUOTE] = cmd_analyze;
	analyze[A_END][P_BQUOTE] = cmd_analyze;
	analyze[A_END][P_QUOTE] = cmd_analyze;
	analyze[A_END][P_ESCSEQ] = cmd_analyze;
	analyze[A_END][P_DBPARENT] = cmd_analyze;
	analyze[A_END][P_PARENT] = cmd_analyze;
	analyze[A_END][P_BRACKET] = cmd_analyze;
	analyze[A_END][P_HOOK] = cmd_analyze;
	analyze[A_END][P_DOLLAR] = cmd_analyze;
	analyze[A_END][P_TILDE] = cmd_analyze;
	analyze[A_END][P_TILDEM] = cmd_analyze;
	analyze[A_END][P_TILDEP] = cmd_analyze;
}

void	init_separator_analyze(t_anal analyze)
{
	analyze[A_SEPARATOR][P_AND] = separator_analyze;
	analyze[A_SEPARATOR][P_PIPE] = separator_analyze;
	analyze[A_SEPARATOR][P_GREAT] = redirect_analyze;
	analyze[A_SEPARATOR][P_GREATAND] = redirect_analyze;
	analyze[A_SEPARATOR][P_LESS] = redirect_analyze;
	analyze[A_SEPARATOR][P_LESSAND] = redirect_analyze;
	analyze[A_SEPARATOR][P_DGREAT] = redirect_analyze;
	analyze[A_SEPARATOR][P_DLESS] = redirect_analyze;
	analyze[A_SEPARATOR][P_DLESSDASH] = redirect_analyze;
	analyze[A_SEPARATOR][P_SEMICOLON] = separator_analyze;
	analyze[A_SEPARATOR][P_NEWLINE] = end_analyze;
	analyze[A_SEPARATOR][P_WORD] = cmd_analyze;
	analyze[A_SEPARATOR][P_BQUOTE] = cmd_analyze;
	analyze[A_SEPARATOR][P_DBQUOTE] = cmd_analyze;
	analyze[A_SEPARATOR][P_QUOTE] = cmd_analyze;
	analyze[A_SEPARATOR][P_ESCSEQ] = cmd_analyze;
	analyze[A_SEPARATOR][P_DBPARENT] = cmd_analyze;
	analyze[A_SEPARATOR][P_PARENT] = cmd_analyze;
	analyze[A_SEPARATOR][P_BRACKET] = cmd_analyze;
	analyze[A_SEPARATOR][P_HOOK] = cmd_analyze;
	analyze[A_SEPARATOR][P_DOLLAR] = cmd_analyze;
	analyze[A_SEPARATOR][P_TILDE] = cmd_analyze;
	analyze[A_SEPARATOR][P_TILDEP] = cmd_analyze;
	analyze[A_SEPARATOR][P_TILDEM] = cmd_analyze;
	analyze[A_SEPARATOR][P_END] = end_analyze;
}
