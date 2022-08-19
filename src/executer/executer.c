/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 20:01:20 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "executer.h"

t_status	do_command(t_btree_node *const left_leaf)
{
	t_btree_node	*node;
	t_cmd			cmd;

	node = left_leaf;
	while (node->parent && get_node_token_kind(node->parent) != TK_PIPE)
	{
		do_token_purpose(node, &cmd);
		node = node->parent;
	}
	execve(cmd.cmd_string, cmd.arguments, NULL); // NULL -> envp is global envp..
	free_strings(cmd.arguments);
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
		pid = e_fork();
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
