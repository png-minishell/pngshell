/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 18:45:26 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"
#include "binary_tree.h"

t_btree_node	*get_left_leaf(t_btree_node *const root)
{
	t_btree_node	*node;

	node = root;
	while (node->left_child)
		node = node->left_child;
	return (node);
}

size_t	get_number_of_pipe(t_btree_node *const ast)
{
	t_btree_node	*node;
	size_t			num;

	num = 0;
	node = ast;
	while (node->left_child)
	{
		if (((t_token *)(node->content))->kind == TK_PIPE)
			++num;
		node = node->left_child;
	}
	return (num);
}

t_token_kind	get_node_token_kind(t_btree_node *node)
{
	return (((t_token *)(node->content))->kind);
}

t_btree_node	*get_next_root(t_btree_node *const left_leaf)
{
	t_btree_node	*node;

	node = left_leaf;
	while (node->parent && get_node_token_kind(node->parent) != TK_PIPE)
		node = node->parent;
	return (node);
}

t_status	do_token_purpose(t_btree_node *node, t_cmd *cmd)
{
	const t_token		*token = node->content;
	const t_token_kind	kind = get_node_token_kind(node);
	int					fd;

	if (kind == TK_CMD)
	{
		// get cmd and argument
	}
	else if (kind == TK_LESS)
	{
		fd = open(token->str, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (kind == TK_GREATER)
	{
		fd = open(token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, STDIN_FILENO);
	}
	else if (kind == TK_DOUBLE_LESS)
	{
		fd = open(HEREDOC_FILE_NAME, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		heredoc(fd, ((t_token *)(node->right_child->content))->str);
		close(fd);
		fd = open(HEREDOC_FILE_NAME, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (kind == TK_DOUBLE_GREATER)
	{
		fd = open(token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDIN_FILENO);
	}
	return (FAILED);
}

pid_t	do_command(t_btree_node *const left_leaf)
{
	t_btree_node	*node;
	t_cmd			cmd;

	node = left_leaf;
	while (node->parent && get_node_token_kind(node->parent) != TK_PIPE)
	{
		do_token_purpose(node, &cmd);
		node = node->parent;
	}
	execve(cmd.cmd_string, cmd.arguments, envp); // envp is global envp...
	unlink(HEREDOC_FILE_NAME);
	return (SUCCESS);
}

t_status	executer(t_btree_node *ast)
{
	const size_t	number_of_process = get_number_of_pipe(ast) + 1;
	size_t			index;
	pid_t			pid;
	t_btree_node	*root;
	t_btree_node	*left_leaf;

	index = 0;
	left_leaf = get_left_leaf(ast);
	root = get_next_root(left_leaf);
	while (index < number_of_process)
	{
		// set pipe...
		pid = fork();
		if (pid == 0)
		{
			do_command(left_leaf);
			exit(errno);
		}
		left_leaf = get_left_leaf(root->right_child);
		root = get_next_root(root);
		++index;
	}
	return (SUCCESS);
}
