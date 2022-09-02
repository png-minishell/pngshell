/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:02:20 by mingylee          #+#    #+#             */
/*   Updated: 2022/09/02 16:05:39 by sungjpar         ###   ########.fr       */
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

static void	cd_home(char **envp)
{
	char	*value;

	value = get_value("HOME", envp, g_vars.set);
	if (value[0] == 0)
	{
		ft_putendl_fd("shell: cd: HOME not set", 2);
		errno = 1;
		free(value);
		return ;
	}
	change_envp_value("PWD", value, envp);
	chdir(value);
	free(value);
}

static void	cd_oldpwd(char **envp)
{
	char	*old_dir;
	char	*current_dir;

	old_dir = get_value("OLDPWD", envp, g_vars.set);
	current_dir = get_value("PWD", envp, g_vars.set);
	if (old_dir[0] == 0)
	{
		ft_putendl_fd("shell: cd: OLDPWD not set", 2);
		errno = 1;
		free(old_dir);
		free(current_dir);
		return ;
	}
	change_envp_value("PWD", old_dir, envp);
	change_envp_value("OLDPWD", current_dir, envp);
	ft_putendl_fd(old_dir, 1);
	chdir(old_dir);
	free(old_dir);
	free(current_dir);
}

static void	put_err(char *err)
{
	ft_putstr_fd("shell: cd: ", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd(": No such file or directory:", 2);
	errno = 1;
}

static int	run_cd(char **arguments, char **envp)
{
	struct stat	buf;

	if (arguments[1] == NULL || ft_strncmp("~", arguments[1], -1) == 0)
	{
		cd_home(envp);
		return (SUCCESS);
	}
	if (ft_strncmp("-", arguments[1], -1) == 0)
	{
		cd_oldpwd(envp);
		return (SUCCESS);
	}
	if (get_file_type(arguments[1], &buf) != TYPE_CHR \
		&& get_file_type(arguments[1], &buf) != TYPE_DIRECTORY)
	{
		put_err(arguments[1]);
		return (errno);
	}
	return (-1);
}

int	builtin_cd(char **arguments, char **envp)
{
	char	*now_dir;
	int		status;

	now_dir = getcwd(NULL, 0);
	if (now_dir == NULL)
	{
		cd_home(envp);
		free(now_dir);
		return (SUCCESS);
	}
	status = run_cd(arguments, envp);
	if (status != -1)
	{
		free(now_dir);
		return (errno);
	}
	change_envp_value("OLDPWD", now_dir, envp);
	change_envp_value("PWD", arguments[1], envp);
	free(now_dir);
	if (!chdir(arguments[1]))
		return (errno);
	return (SUCCESS);
}
