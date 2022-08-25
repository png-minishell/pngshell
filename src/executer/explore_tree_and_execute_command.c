/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_tree_and_execute_command.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:02:54 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:19:15 by sungjpar         ###   ########.fr       */
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

void	explore_tree_and_execute_command(\
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
			analyze_and_execute_command(left_leaf);
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
