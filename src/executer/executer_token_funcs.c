/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_token_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:26:28 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 19:33:32 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "binary_tree.h"
#include "executer.h"
#include "minishell_definitions.h"

t_status	do_infile_redirection(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}

t_status	do_outfile_redirection(const char *path, int flag, int mode)
{
	int	fd;

	fd = open(path, flag, mode);
	dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}

t_status	do_heredoc_redirection(t_btree_node *const node)
{
	int	fd;

	fd = open(HEREDOC_FILE_NAME, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	heredoc(fd, ((t_token *)(node->right_child->content))->str);
	close(fd);
	fd = open(HEREDOC_FILE_NAME, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}
