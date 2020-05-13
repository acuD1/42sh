/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:12:41 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/12 12:24:47 by fcatusse         ###   ########.fr       */
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

static void		print_ac_lst(size_t elem_line, , size_t *nb, t_auto_comp *ac)
{
	if (elem_line != 1)
	{
		if (nb == elem_line)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			nb = 0;
		}
		ft_dprintf(STDERR_FILENO, "%-*s", ac->max_len + 1, ac->lst->content);
		nb++;
	}
	else
		ft_dprintf(STDERR_FILENO, "%s\n", ac->lst->content);
}

void			display_ac_lst(t_auto_comp *ac)
{
	size_t		elem_line;
	size_t		nb;
	t_lst		*head;

	if (!ac->lst)
		return ;
	elem_line = ac->ws_col / ac->max_len;
	if (!elem_line)
		elem_line = 1;
	nb = 0;
	ft_lstsort(&ac->lst, ft_lstcmp);
	head = ac->lst;
	ft_putchar_fd('\n', STDERR_FILENO);
	if (ac->lst_size > 100 && display_confirmed(ac) == FAILURE)
		return ;
	while (ac->lst)
	{
		print_ac_lst(elem_line, &nb, ac);
		ac->lst = ac->lst->next;
	}
	ac->lst = head;
}
