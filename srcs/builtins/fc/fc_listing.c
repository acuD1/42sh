/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_listing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:11:54 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/08 19:30:05 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		sort_range(t_lst *w, int16_t *len, u_int16_t *n, char **range)
{
	if (ft_atoi(range[0]) > 0 && ft_atoi(range[1]) > 0)
	{
		*len = ft_lstlen(w) - ft_atoi(range[0]);
		*n = ft_atoi(range[1]) + 1;
		if (ft_atoi(range[0]) > ft_atoi(range[1]))
			(*n) -= 2;
	}
	else if (ft_atoi(range[0]) < 0 || ft_atoi(range[1]) < 0)
	{
		if (ft_atoi(range[1]) > 0)
		{
			*n = ft_atoi(range[1]) - 1;
			*len = ft_atoi(range[0]) * (-1);
		}
		else
		{
			*n = ft_lstlen(w) + ft_atoi(range[1]) - 1;
			if (ft_atoi(range[0]) < 0)
				*len = ft_atoi(range[0]) * (-1);
			else
				*len = ft_lstlen(w) - ft_atoi(range[0]);
		}
	}
}

u_int16_t	set_range(t_lst **w, char **range)
{
	int16_t		len;
	u_int16_t	n;

	len = 0;
	n = ft_lstlen(*w);
	if (ft_tablen(range) == 0)
		len = 17;
	else if (ft_atoi(range[0]) > n)
		return (ft_lstlen(*w) - 1);
	else if (ft_tablen(range) >= 2)
	{
		sort_range(*w, &len, &n, range);
		if ((ft_atoi(range[0]) < 0 && ft_atoi(range[1]) > 0)
			|| (ft_atoi(range[0]) > 0 && ft_atoi(range[1]) < 0))
			swap_range(&range[0], &range[1]);
	}
	else if (ft_atoi(range[0]) < 0)
		len = ft_atoi(range[0]) * (-1);
	else if (ft_atoi(range[0]) > 0)
		len = ft_lstlen(*w) - ft_atoi(range[0]);
	else if (len < 0 || ft_atoi(range[0]) == 0)
		len = 1;
	while ((*w)->next && len-- > 0)
		*w = (*w)->next;
	return (n);
}

void		listing_mode(t_lst *saved, u_int64_t opt, char **range)
{
	u_int16_t	n;

	n = 0;
	if (opt & (1ULL << 17))
	{
		display_reverse(saved, opt, range);
		return ;
	}
	else
		n = set_range(&saved, range);
	while (saved && n != saved->content_size)
	{
		if ((opt & (1ULL << 13)))
			ft_dprintf(STDOUT_FILENO, "\t%s\n", saved->content);
		else
			ft_dprintf(STDOUT_FILENO, "%d\t%s\n", saved->content_size, saved->content);
		if (range[0] && range[1] && ft_atoi(range[0]) > ft_atoi(range[1]))
			saved = saved->next;
		else
			saved = saved->prev;
	}
}
