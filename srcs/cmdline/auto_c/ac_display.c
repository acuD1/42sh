/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:12:41 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/14 17:10:50 by fcatusse         ###   ########.fr       */
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

static size_t	get_nb_col(t_auto_comp *ac)
{
	size_t			by_col;
	size_t			by_line;

	if (ac->max_len <= 0)
		ac->max_len = 1;
	if ((by_line = ac->ws_col / ac->max_len) == 0)
		by_line = 1;
	by_col = ac->lst_size / by_line;
	if (ac->lst_size % by_line)
		by_col++;
	return (by_col);
}

static void		walking_and_display(t_auto_comp *ac, size_t nb_col, size_t i)
{
	size_t		nb;
	t_lst		*w;

	nb = i;
	w = ac->lst;
	while (nb > 0 && w != NULL)
	{
		w = w->next;
		nb--;
	}
	while (w != NULL)
	{
		if (nb % nb_col == 0)
			ft_dprintf(STDERR_FILENO, "%-*s", ac->max_len, w->content);
		w = w->next;
		nb++;
	}
}

void			display_ac_lst(t_auto_comp *ac)
{
	size_t		nb_col;
	size_t		i;

	i = 0;
	if (!ac->lst)
		return ;
	ac->max_len++;
	nb_col = get_nb_col(ac);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (ac->lst_size > 100 && display_confirmed(ac) == FAILURE)
		return ;
	ft_lstsort(&ac->lst, ft_lstcmp);
	while (i < nb_col)
	{
		walking_and_display(ac, nb_col, i);
		i++;
		if (i != nb_col)
			ft_putchar_fd('\n', STDERR_FILENO);
	}
}
