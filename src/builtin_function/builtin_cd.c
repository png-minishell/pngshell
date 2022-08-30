/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:02:20 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/30 21:30:46 by sungjpar         ###   ########.fr       */
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
		free(value);
		return ;
	}
	chdir(value);
	free(value);
}

static void	cd_oldpwd(char **envp)
{
	char	*value;

	value = get_value("OLDPWD", envp, g_vars.set);
	if (!value)
	{
		ft_putendl_fd("shell: cd: OLDPWD not set", 2);
		return ;
	}
	ft_putendl_fd(value, 1);
	chdir(value);
	free(value);
}

static void	put_err(char *err)
{
	ft_putstr_fd("shell: cd: no such file or directory:", 2);
	ft_putendl_fd(err, 2);
}

static int	run_cd(char **arguments, char **envp, char *now_dir)
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
		free(now_dir);
		return (errno);
	}
	return (-1);
}

int	builtin_cd(char **arguments, char **envp)
{
	char	*now_dir;
	int		status;

	now_dir = getcwd(NULL, 0);
	status = run_cd(arguments, envp, now_dir);
	if (status != -1)
		return (status);
	change_envp_value("PWD", arguments[1], envp);
	change_envp_value("OLDPWD", now_dir, envp);
	free(now_dir);
	if (!chdir(arguments[1]))
		return (errno);
	return (SUCCESS);
}
