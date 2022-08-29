/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:02:20 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 17:40:07 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "minishell_definitions.h"

int	builtin_cd(const char *str, char **arguments, char **envp)
{
	char		*now_dir;
	char		*change_dir;
	struct stat	buf;

	now_dir = getcwd(NULL, 0);
	if (arguments[1] == NULL)
		chdir(get_value("HOME=", envp, set));
	// arguments가 "cd 'path'" 로 들어와야됨
	// cd 만 입력할 경우 $홈으로
	// cd args1 args2 args3 처럼 입력시 args1로만 이동함
	if (what_is_this_file(arguments[1], &buf) != 1 || what_is_this_file(arguments[1], &buf) != 2)
		return (errno);
	change_envp_value("PWD=", arguments[1], envp);
	if (get_value("OLD_PWD=", envp, set))
	{
		change_envp_value("OLD_PWD=", now_dir, envp);
	}
	if (!chdir(arguments[1]))
		return (errno);
	free(now_dir);
	return (SUCCESS);
}
