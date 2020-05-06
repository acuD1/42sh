//GEPA INSTALLE LE TRUC POUR LES HEADERS SORRY :/

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
