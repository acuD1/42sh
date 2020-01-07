/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:59:34 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/07 18:27:38 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t debugo(const char *path, int i, int j, char *str, char *tmp)
{
    int fd;

    if ((fd = open(path, O_WRONLY)) < 0)
        return (-1);
    dprintf(fd,"i[%d] j{%d} \"%s\" tmp[%s]\n", i,j,str, tmp);
    return (1);
}

/*
**		To insert in buffer the content found from the hst lst
*/

int			insert_content(int j, int i, t_read *term, char *content)
{
	char		*tmp;
	int			len;
	int			inc_len;

(void)j;
	len = i + ft_strlen(content);
	inc_len = 0;
	if (i >= BUFF_SIZE)
	{
		inc_len = ft_strlen(term->buffer) + ft_strlen((char *)content);
		term->buffer = realloc(term->buffer, inc_len);
	}
	tmp = ft_strsub(term->buffer, i + 2, term->width - term->prompt_len);
	debugo("/dev/ttys001",i,j,content, tmp);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE);
	term->width = term->prompt_len;
	insert_str_in_buffer(content, term);
	insert_str_in_buffer(tmp, term);
	ft_strdel(&tmp);
	/* len = term->width - term->prompt_len - j; */
	/* tmp = ft_strsub(term->buffer, i + j, len); */
	/* j = -1; */
	/* while (((char*)content)[++j]) */
	/* { */
	/* 	term->buffer[i] = ((char *)content)[j]; */
	/* 	i++; */
	/* } */
	/* j = -1; */
	/* len = i; */
	/* while (tmp[++j]) */
	/* 	term->buffer[i++] = tmp[j]; */
	/* term->buffer[i] = 0; */
	/* ft_strdel(&tmp); */
	return (len - 1);
}

/*
**		"!word" expansion search the word to find from the end of hst lst
*/

void			call_word(t_read *term, int i)
{
	char		word[BUFF_SIZE];
	int			j;
	int			n;
	t_lst		*w;

	j = -1;
	w = term->history;
	n = i + 1;
	while (n < (int)ft_strlen(term->buffer) && !ft_isblank(term->buffer[n]))
	{
		word[++j] = term->buffer[n];
		n++;
	}
	word[j + 1] = '\0';
	if (!w || n > (int)ft_lstlen(w) || n > HIST_SIZE)
		return ;
	while (w->next)
	{
		if (isstart((char *)w->content, word))
			break ;
		w = w->next;
	}
	if (!w->next)
		return ;
	insert_content(j + 2, i, term, (char *)w->content);
}

/*
**		"!-number" expansion search from the end of hst lst
*/

void			callback_number(t_read *term, int i)
{
	char		nb[BUFF_SIZE];
	int			n;
	t_lst		*w;
	int			j;

	j = -1;
	w = term->history;
	n = i + 2;
	while (ft_isdigit(term->buffer[n]))
	{
		nb[++j] = term->buffer[n];
		n++;
	}
	n = ft_atoi(nb);
	if (!w || n > (int)ft_lstlen(w) || n > HIST_SIZE || n < 0)
		return ;
	while (w && n != 0 && --n)
	{
		if (w->next)
			w = w->next;
	}
	insert_content(j + 3, i, term, (char *)w->content);
	i = i + j + 1;
}

/*
**		"!number" expansion search from the beggining of hst lst
*/

void			call_number(t_read *term, int i)
{
	char		nb[BUFF_SIZE];
	int			n;
	t_lst		*w;
	int			j;

	j = -1;
	w = term->history;
	n = i + 1;
	while (ft_isdigit(term->buffer[n]))
	{
		nb[++j] = term->buffer[n];
		n++;
	}
	n = ft_atoi(nb);
	if (!w || n > (int)ft_lstlen(w) || n > HIST_SIZE || n < 0)
		return ;
	while (w->next)
		w = w->next;
	while (w && n != 0 && --n)
		if (w->prev)
			w = w->prev;
	insert_content(j + 2, i, term, (char *)w->content);
	i = i + j + 1;
}

/*
**		"!!" expansion search the last occurence of hst list
*/

void		last_cmd_back(t_read *term, int i)
{
	t_lst		*w;

	w = term->history;
	if (!term->history || ft_strlen(term->buffer) > BUFF_SIZE)
		return ;
	if (w && w->content)
		insert_content(2, i, term, (char *)w->content);
//	debugo("/dev/ttys001",i,ft_strlen((char*)w->content),NULL, NULL);
}
