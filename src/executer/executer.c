/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/22 21:51:08 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "executer.h"

static void	wait_childs(pid_t *pid, size_t number_of_process)
{
	size_t	index;

	index = 0;
	while (index < number_of_process)
	{
		waitpid(pid[index++], NULL, 0);
	}
}

/* main executer function*/
t_status	execute_commands_from_ast(t_btree_node *ast)
{
	const size_t	number_of_process = get_number_of_pipe(ast) + 1;
	pid_t			*pid;

	pid = e_malloc(sizeof(pid_t) * number_of_process);
	run_commands(ast, pid, number_of_process);
	wait_childs(pid, number_of_process);
	free(pid);
	return (SUCCESS);
}
