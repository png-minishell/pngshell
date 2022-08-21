/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:53:48 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 15:50:42 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "error_control_functions.h"
#include "executer.h"

t_status	set_pipe(int no_cmd, int number_of_cmds, int pipelines[2][2])
{
	const int	my_pipe_index = no_cmd & 1;
	const int	prev_pipe_index = !my_pipe_index;

	if (no_cmd == number_of_cmds - 1)
		e_dup2(pipelines[my_pipe_index][PIPE_INDEX_WRITE], STDOUT_FILENO);
	if (no_cmd != 0)
	{
		e_close(pipelines[prev_pipe_index][PIPE_INDEX_WRITE]);
		e_dup2(pipelines[prev_pipe_index][PIPE_INDEX_READ], STDIN_FILENO);
	}
	e_close(pipelines[my_pipe_index][PIPE_INDEX_READ]);
	return (SUCCESS);
}
