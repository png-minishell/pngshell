/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:49:00 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 19:36:49 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include "minishell_definitions.h"

int	get_file_type(char *file, struct stat *file_buf)
{
	if (stat(file, file_buf) == -1)
		return (errno);
	if (S_ISFIFO(file_buf->st_mode) == TRUE)
		return (TYPE_FIFO);
	else if (S_ISCHR(file_buf->st_mode) == TRUE)
		return (TYPE_CHR);
	else if (S_ISDIR(file_buf->st_mode) == TRUE)
		return (TYPE_DIRECTORY);
	else if (S_ISBLK(file_buf->st_mode) == TRUE)
		return (TYPE_BLOCK);
	else if (S_ISREG(file_buf->st_mode) == TRUE)
		return (TYPE_REGULAR);
	else if (S_ISLNK(file_buf->st_mode) == TRUE)
		return (TYPE_LINK);
	else if (S_ISSOCK(file_buf->st_mode) == TRUE)
		return (TYPE_SOCKET);
	return (-1);
}

int	check_permission(char *absolute_path)
{
	struct stat	buf;

	if (get_file_type(absolute_path, &buf) != TYPE_REGULAR
		&& get_file_type(absolute_path, &buf) != TYPE_LINK)
		return (FALSE);
	if ((buf.st_mode & S_IXUSR) != 0)
		return (TRUE);
	return (FALSE);
}
