/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:12:52 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 14:27:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>
#include <unistd.h>

static int8_t	other_tests(const char *path, int opt, struct stat buf)
{
	if (opt == R_UNATEST)
		return ((buf.st_mode & S_IRUSR) ? 0 : 1);
	if (opt == SS_UNATEST)
		return (S_ISSOCK(buf.st_mode) ^ 1);
	if (opt == S_UNATEST)
		return ((buf.st_size > 0) ? 0 : 1);
	if (opt == U_UNATEST && buf.st_mode & S_IXUSR)
		return ((buf.st_mode & S_ISUID) ? 0 : 1);
	if (opt == W_UNATEST)
		return ((buf.st_mode & S_IWUSR) ? 0 : 1);
	if (opt == X_UNATEST)
		return ((buf.st_mode & S_IXUSR) ? 0 : 1);
	return ((path[0] == 0) ? 0 : 1);
}

int8_t			path_tests(const char *path, int opt)
{
	struct stat	buf;
	char		buffer[MAX_PATH + 1];

	if (get_canonical_path(NULL, path, buffer, NULL) != SUCCESS
	|| ((opt == LL_UNATEST) ? lstat(path, &buf) : stat(path, &buf)) < 0)
		return (1);
	if (opt == B_UNATEST)
		return (S_ISBLK(buf.st_mode) ^ 1);
	if (opt == C_UNATEST)
		return (S_ISCHR(buf.st_mode) ^ 1);
	if (opt == D_UNATEST)
		return (S_ISDIR(buf.st_mode) ^ 1);
	if (opt == E_UNATEST)
		return (access(path, F_OK == 0) ? 0 : 1);
	if (opt == F_UNATEST)
		return (S_ISREG(buf.st_mode) ^ 1);
	if (opt == G_UNATEST && buf.st_mode & S_IXGRP)
		return ((buf.st_mode & S_ISGID) ? 0 : 1);
	if (opt == LL_UNATEST)
		return (S_ISLNK(buf.st_mode) ^ 1);
	if (opt == P_UNATEST)
		return (S_ISFIFO(buf.st_mode) ^ 1);
	return (other_tests(buffer, opt, buf));
}
