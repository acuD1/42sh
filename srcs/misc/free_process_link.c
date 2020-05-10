/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_process_link.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 13:27:51 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/10 13:27:58 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	free_process_link(t_lst *ptr)
{
	if (ptr && ptr->content)
	{
		ft_free_redirlist((t_lst **)&(((t_process *)ptr->content)->redir_list));
		free_db((((t_process *)ptr->content)->assign_list));
		ft_freetokenlist(&(((t_process *)ptr->content)->tok_list));
		ft_tabdel(&(((t_process *)ptr->content)->av));
		ft_tabdel(&(((t_process *)ptr->content)->envp));
		ft_strdel(&(((t_process *)ptr->content)->bin));
		ft_strdel(&(((t_process *)ptr->content)->command));
		free(ptr->content);
		free(ptr);
	}
}
