/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/30 10:53:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
**	Some build data
*/

typedef struct	s_build
{
	u_int8_t	release;
	u_int8_t	version;
	u_int16_t	patch;
	u_int32_t	date;
}				t_build;

/*
**	t_db is formated to support environnement variables ; {key} and {value}
*/

typedef struct	s_db
{
	char		*key;
	char		*value;
}				t_db;

/*
**	t_core shares global variables
*/

typedef struct	s_core
{
	/* structs */
	t_build		build;
	t_hash		hash;			// Gonna call it on the stack for now
	t_db		db;

	/* lists */
	t_lst		*env;

	/* variables */
	char		**tokens;		//	ft_strplit of char *line from GNL [BETA]
	char		*bin;			//	dup of the binary found or located [BETA]
	u_int8_t	opt;			//	Options

}				t_core;

/*
**	t_hash for hash table implementation
*/

typedef struct	s_hash
{
	char		**table;
	u_int32_t	value;
	u_int32_t	size;
}				t_hash;

#endif
