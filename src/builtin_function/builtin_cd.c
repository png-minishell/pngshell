/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:02:20 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 20:23:59 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "minishell_definitions.h"
#include "libft.h"

int	builtin_cd(char **arguments, char **envp)
{
	char		*now_dir;
	struct stat	buf;

	now_dir = getcwd(NULL, 0);
	if (arguments[1] == NULL)
	{
		chdir(get_value("HOME=", envp, set));
		return (SUCCESS);
	}
	if (get_file_type(arguments[1], &buf) != TYPE_CHR \
		|| get_file_type(arguments[1], &buf) != TYPE_DIRECTORY)
	{
		ft_putstr_fd("shell: cd: no such file or directory:", 2);
		ft_putendl_fd(arguments[1], 2);
		free(now_dir);
		return (errno);
	}
	change_envp_value("PWD=", arguments[1], envp);
	if (get_value("OLD_PWD=", envp, set))
		change_envp_value("OLD_PWD=", now_dir, envp);
	free(now_dir);
	if (!chdir(arguments[1]))
		return (errno);
	return (SUCCESS);
}
