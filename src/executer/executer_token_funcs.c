/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_token_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:26:28 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/23 15:02:10 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "binary_tree.h"
#include "executer.h"
#include "error_control_functions.h"
#include "libft.h"
#include "minishell_definitions.h"

t_status	do_infile_redirection(const char *path)
{
	int	fd;

	if (path[0] == 0)
		e_dup2(stdin_bak, STDIN_FILENO);
	else
	{
		fd = e_open(path, O_RDONLY, 0644);
		e_dup2(fd, STDIN_FILENO);
	}
	return (SUCCESS);
}

t_status	do_outfile_redirection(const char *path, int flag, int mode)
{
	int	fd;

	fd = e_open(path, flag, mode);
	e_dup2(fd, STDOUT_FILENO);
	return (SUCCESS);
}

t_status	do_heredoc_redirection(const int fd)
{
	e_dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}
