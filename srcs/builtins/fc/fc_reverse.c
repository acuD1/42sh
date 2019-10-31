/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:55:43 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/31 22:31:31 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		swap_range(char **r1, char **r2)
{
	char	*tmp;

	tmp = NULL;
	tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

void		sort_range(t_lst *w, int *ret, size_t *num, char **range)
{
	if (ft_atoi(range[0]) > ft_atoi(range[1]))
		swap_range(&range[0], &range[1]);
	if (ft_atoi(range[0]) == 0 && ft_atoi(range[1]) == 0)
		*ret = ft_lstlen(w);
	else if (ft_atoi(range[0]) < 0 || ft_atoi(range[1]) < 0)
	{
		if (ft_atoi(range[1]) > 0)
			*ret = ft_atoi(range[1]);
		else
			*ret = ft_lstlen(w) + ft_atoi(range[1]) - 2;
		if (ft_atoi(range[1]) < 0)
			*num = ft_lstlen(w) + ft_atoi(range[1]) + 2;
		else
			*num = ft_lstlen(w) - ft_atoi(range[1]) + 2;
	}
	else if (ft_atoi(range[0]) > 0 && ft_atoi(range[1]) > 0)
	{
		*num = ft_atoi(range[1]);
		*ret = ft_atoi(range[0]);
	}
	else if (ft_atoi(range[0]) == 0)
		*ret = ft_atoi(range[1]);
}

u_int16_t	reverse_range(t_lst **w, char **range)
{
	size_t  	number;
	int		ret;

	number = 1;
	ret = 0;
	if (ft_tablen(range) == 1)
		if (ft_atoi(range[0]) <= 0)
			return (ret = ft_lstlen(*w) + ft_atoi(range[0]));
		else
			return (ret = ft_atoi(range[0]));
	else if (ft_tablen(range) >= 2)
	{
		sort_range(*w, &ret, &number, range);
		if (ft_atoi(range[0]) == 0)
			number = ft_lstlen(*w);
	}
	else
		return (ret = ft_lstlen(*w) - 17);
	while ((*w)->next && number != (*w)->content_size)
		*w = (*w)->next;
	return (ret);
}

void		display_reverse(t_lst *w, u_int64_t opt, char **range)
{
	u_int16_t	n;

	if ((n = reverse_range(&w, range)) > ft_lstlen(w))
		n = 1;
	while (w && n <= w->content_size)
	{
		if ((opt & (1ULL << 13)))
			ft_dprintf(STDOUT_FILENO, "\t%s\n", w->content);
		else
			ft_dprintf(STDOUT_FILENO, "%d\t%s\n", w->content_size, w->content);
		w = w->next;
	}
}
