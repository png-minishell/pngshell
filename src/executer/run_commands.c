/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:02:54 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/22 21:32:38 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "error_control_functions.h"
#include "executer.h"
#include "libft.h"

static t_status	do_command(t_btree_node *const left_leaf)
{
	t_btree_node	*node;
	t_cmd			cmd;

	node = left_leaf;
	cmd.path = NULL;
	cmd.argv = NULL;
	while (get_node_token_kind(node) != TK_PIPE)
	{
		do_token_purpose(node, &cmd);
		node = node->parent;
		if (node == NULL)
			break ;
	}
	if (cmd.path == NULL)
	{
		cmd.path = find_execute_file_path("cat");
		cmd.argv = e_malloc(sizeof(char *) * 2);
		cmd.argv[0] = ft_strdup("cat");
		cmd.argv[1] = NULL;
	}
	if (execve(cmd.path, cmd.argv, envp) != SUCCESS)
		perror(cmd.path); // NULL -> envp is global envp..
	return (SUCCESS);
}

static void	close_unused_pipe(\
	int no_cmd, int pipelines[2][2])
{
	const int	unused_pipe_idx = no_cmd & 1;

	if (no_cmd <= 1)
		return ;
	else
	{
		e_close(pipelines[unused_pipe_idx][PIPE_INDEX_READ]);
		e_close(pipelines[unused_pipe_idx][PIPE_INDEX_WRITE]);
	}
}

static pid_t	build_pipe_and_fork(
	int no_cmd, int pipelines[2][2])
{
	pid_t	pid;

	close_unused_pipe(no_cmd, pipelines);
	e_pipe(pipelines[no_cmd & 1]);
	pid = e_fork();
	return (pid);
}

void	run_commands(\
	t_btree_node *ast, pid_t *pid, const size_t number_of_process)
{
	size_t			index;
	int				pipelines[2][2];
	t_btree_node	*left_leaf;
	t_btree_node	*root;

	index = 0;
	left_leaf = get_left_leaf(ast);
	root = get_next_root(left_leaf);
	while (index < number_of_process)
	{
		pid[index] = build_pipe_and_fork(index, pipelines);
		if (pid[index] == 0)
		{
			set_pipe(index, number_of_process, pipelines);
			do_command(left_leaf);
			write(1, 0, 1);
			exit(errno);
		}
		if (root->right_child)
			left_leaf = get_left_leaf(root->right_child);
		root = get_next_root(root);
		++index;
	}
	close_unused_pipe(index++, pipelines);
	close_unused_pipe(index++, pipelines);
}
