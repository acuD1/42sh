/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/14 15:13:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
**	Global
*/

# define SUCCESS		0
# define FAILURE		-1
# define FALSE			0
# define TRUE			1

/*
**	Color
*/
# define C_R			"\x1b[31m"
# define C_G			"\x1b[32m"
# define C_Y			"\x1b[33m"
# define C_B			"\x1b[34m"
# define C_M			"\x1b[35m"
# define C_C			"\x1b[36m"
# define C_X			"\x1b[0m"

/*
**	Free
*/

# define FREE_1			1
# define FREE_2			2
# define FREE_ALL		3

/*
**	Option
*/

# define OPT_VERS		0x001
# define OPT_HELP		0x002

/*
**	Exec handler
*/

# define BIN_ERROR		0x001
# define PATH_ERROR		0x002
# define FORK_ERROR		0x004
# define PERM_ERROR		0x008
# define EXEC_ERROR		0x010

/*
**	Hash table
*/

# define HASH_SIZE		4096
# define MAX_LOAD_F		0.75

/*	
**	===========================================================================
**	INTERN SHELL VARIABLES.....................................................
**	===========================================================================
*/

#define ENV_VAR			0x001
#define SET_VAR			0x002
#define INTERN_VAR		0x004


#endif
