/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 15:46:01 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "executer.h"

static void	free_strings(char **strings)
{
	size_t	index;

	index = 0;
	while (strings[index])
		free(strings[index]);
	free(strings);
}

static t_status	do_command(t_btree_node *const left_leaf)
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

static void	close_unused_pipe(\
	int no_cmd, int pipelines[2][2], const int number_of_commands)
{
	const int	unused_pipe_idx = no_cmd & 1;

	if (no_cmd == 0)
		return ;
	else
	{
		e_close(pipelines[unused_pipe_idx][PIPE_INDEX_READ]);
		e_close(pipelines[unused_pipe_idx][PIPE_INDEX_WRITE]);
	}
}

static pid_t	build_pipe_and_fork(
	int no_cmd, int pipelines[2][2], const int number_of_commands)
{
	pid_t	pid;

	close_unused_pipe(no_cmd, pipelines, number_of_commands);
	e_pipe(pipelines[no_cmd & 1]);
	pid = e_fork();
	return (pid);
}

t_status	executer(t_btree_node *ast)
{
	const size_t	number_of_process = get_number_of_pipe(ast) + 1;
	size_t			index;
	pid_t			*pid;
	int				pipelines[2][2];
	t_btree_node	*root;
	t_btree_node	*left_leaf;

	index = 0;
	pid = e_malloc(sizeof(pid_t) * number_of_process);
	left_leaf = get_left_leaf(ast);
	root = get_next_root(left_leaf);
	while (index < number_of_process)
	{
		build_pipe_and_fork(index, pipelines, number_of_process);
		pid[index] = e_fork();
		if (pid == 0)
		{
			set_pipe(index, number_of_process, pipelines);
			do_command(left_leaf);
			exit(errno);
		}
		left_leaf = get_left_leaf(root->right_child);
		root = get_next_root(root);
		++index;
	}
	index = 0;
	while (index < number_of_process)
	{
		waitpid(pid[index], NULL, 0);
		++index;
	}
	return (SUCCESS);
}
