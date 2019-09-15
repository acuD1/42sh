/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/15 19:01:41 by mpivet-p         ###   ########.fr       */
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
	u_int8_t	type;
	u_int32_t	hit;		// Only for hash_map
}				t_db;

/*
**	t_hash and his db for hash table implementation
*/

typedef struct	s_hash
{
	t_lst		**map;
	u_int32_t	value;
	u_int32_t	size;			// Size located
	u_int32_t	lenght;			// Numbers of keys
}				t_hash;

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
	char		*buff;
	char		**tokens;		//	ft_strplit of char *line from GNL [BETA]
	char		*bin;			//	dup of the binary found or located [BETA]
	u_int8_t	opt;			//	Option
}				t_core;


#endif
