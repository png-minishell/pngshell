/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:10:45 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/29 18:11:11 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "minishell_definitions.h"
#include "executer.h"

t_status	run_builtin(const char *str, char **arguments, char **envp)
{
	enum e_builtin_kind	builtin;

	builtin = check_builtin(str);
	/*if (builtin == BT_ECHO)
		builtin_echo(str, arguments, envp);
	*/
	if (builtin == BT_CD)
		builtin_cd(str, arguments, envp);
	/*
	else if (builtin == BT_PWD)
		builtin_pwd(str, arguments, envp);
	else if (builtin == BT_EXPORT)
		builtin_export(str, arguments, envp);
	else if (builtin == BT_UNSET)
		builtin_unset(str, arguments, envp);
	else if (builtin == BT_ENV)
		builtin_env(envp);
	else if (builtin == BT_EXIT)
		builtin_exit(str, arguments, envp);
	*/
	return (SUCCESS);
}

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
