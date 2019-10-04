/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/10/04 05:09:41 by mpivet-p         ###   ########.fr       */
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
**	t_db is formated to support environnement variables ; {key}, {value} and {type}
*/

typedef struct	s_db
{
	char		*key;
	char		*value;
	u_int8_t	type;
	u_int32_t	hit;		// Only for hash_map
}				t_db;

/*
**	t_process is formated to contain background processes
*/

typedef struct	s_process
{
	char		*name;
	pid_t		pid;
	u_int16_t	bck_order;	// Background place order (0 = last)
	u_int16_t	bck_id;		// Background id
}				t_process;

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
	t_lst		*pos_vars;
	t_lst		*jobs;

	/* variables */
	char		*buff;
	char		**tokens;			//	ft_strplit of char *line from GNL [BETA]
	char		*bin;				//	dup of the binary found or located [BETA]
	int32_t		last_exit_status;	//	last exit status value (echo $?)
	u_int8_t	opt;				//	Option
}				t_core;


#endif
