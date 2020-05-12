/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:12:41 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/12 12:05:15 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

static int8_t	display_confirmed(t_auto_comp *ac)
{
	char	buff[2];

	ft_bzero(buff, 2);
	ft_dprintf(STDERR_FILENO,
		"Display all %d possibilities ? (y or n)", ac->lst_size);
	sigint_special_handler();
	if (read(STDIN_FILENO, buff, 1) == FAILURE)
	{
		signal(SIGINT, sigint_handler);
		return (FAILURE);
	}
	signal(SIGINT, sigint_handler);
	if (!ft_strequ(buff, "y"))
		return (FAILURE);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (SUCCESS);
}

int8_t			display_ac_lst(t_auto_comp *ac)
{
	size_t		elem_line;
	size_t		nb;
	t_lst		*head;

	nb = 1;
	if (!ac->lst)
		return (FAILURE);
	elem_line = ac->ws_col / ac->max_len;
	ft_lstsort(&ac->lst, ft_lstcmp);
	head = ac->lst;
	ft_putchar_fd('\n', STDERR_FILENO);
	if (ac->lst_size > 100 && display_confirmed(ac) == FAILURE)
		return (FAILURE);
	while (ac->lst)
	{
		if (elem_line != 0 && nb == elem_line)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			nb = 1;
		}
		ft_dprintf(STDERR_FILENO, "%-*s", ac->max_len + 1, ac->lst->content);
		ac->lst = ac->lst->next;
		nb++;
	}
	ac->lst = head;
	return (SUCCESS);
}
