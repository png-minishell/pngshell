/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_token_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:26:28 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 20:00:14 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "binary_tree.h"
#include "executer.h"
#include "error_control_functions.h"
#include "minishell_definitions.h"

t_status	do_infile_redirection(const char *path)
{
	int	fd;

	fd = e_open(path, O_RDONLY, 0644);
	e_dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}

t_status	do_outfile_redirection(const char *path, int flag, int mode)
{
	int	fd;

	fd = e_open(path, flag, mode);
	e_dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}

t_status	do_heredoc_redirection(t_btree_node *const node)
{
	int	fd;

	fd = e_open(HEREDOC_FILE_NAME, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	heredoc(fd, ((t_token *)(node->right_child->content))->str);
	e_close(fd);
	fd = e_open(HEREDOC_FILE_NAME, O_RDONLY, 0644);
	e_dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}
