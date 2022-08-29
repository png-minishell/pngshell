/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:10:45 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/29 20:23:23 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "minishell_definitions.h"
#include "executer.h"

t_status	run_command(t_token *cmd_token)
{
	char	*path;

	path = find_execute_file_path(cmd_token->str);
	if (path == NULL)
		return (FAILED);
	free(cmd_token->str);
	cmd_token->str = path;
	if (execve(cmd_token->str, cmd_token->arguments, envp) != SUCCESS)
		perror(NULL);
	return (SUCCESS);
}
