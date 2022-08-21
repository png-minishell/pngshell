/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 20:29:24 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "binary_tree.h"
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

#include "libft.h"
static char	*get_cmd_path(const char *str)
{
	if (ft_strncmp(str, "cat", -1) == 0)
		return (ft_strdup("/bin/cat"));
	if (ft_strncmp(str, "echo", -1) == 0)
		return (ft_strdup("/bin/echo"));
	if (ft_strncmp(str, "grep", -1) == 0)
		return (ft_strdup("/usr/bin/grep"));
	if (ft_strncmp(str, "ls", -1) == 0)
		return (ft_strdup("/bin/ls"));
	return (ft_strdup(""));
}

static t_status	do_command(t_btree_node *const left_leaf)
{
	t_btree_node	*node;
	t_cmd			cmd;
	char			*cmd_path;

	node = left_leaf;
	while (get_node_token_kind(node) != TK_PIPE)
	{
		do_token_purpose(node, &cmd);
		node = node->parent;
		if (node == NULL)
			break ;
	}
	cmd_path = get_cmd_path(cmd.cmd_string);
	if (cmd_path[0])
		execve(cmd_path, cmd.arguments, NULL); // NULL -> envp is global envp..
	free(cmd_path);
	free_strings(cmd.arguments);
	unlink(HEREDOC_FILE_NAME);
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

static void	wait_childs(pid_t *pid, size_t number_of_process)
{
	size_t	index;

	index = 0;
	while (index < number_of_process)
		waitpid(pid[index++], NULL, 0);
}

void	run_commands(\
	t_btree_node *ast, pid_t *pid, const size_t number_of_process)
{
	size_t			index;
	int				pipelines[2][2];
	t_btree_node	*left_leaf;
	t_btree_node	*root;

	index = 0;
	pid = e_malloc(sizeof(pid_t) * number_of_process);
	left_leaf = get_left_leaf(ast);
	root = get_next_root(left_leaf);
	while (index < number_of_process)
	{
		pid[index] = build_pipe_and_fork(index, pipelines);
		if (pid[index] == 0)
		{
			set_pipe(index, number_of_process, pipelines);
			do_command(left_leaf);
			exit(errno);
		}
		left_leaf = get_left_leaf(root->right_child);
		root = get_next_root(root);
		++index;
	}
}

t_status	executer(t_btree_node *ast)
{
	const size_t	number_of_process = get_number_of_pipe(ast) + 1;
	pid_t			*pid;

	pid = e_malloc(sizeof(pid_t) * number_of_process);
	run_commands(ast, pid, number_of_process);
	wait_childs(pid, number_of_process);
	return (SUCCESS);
}
