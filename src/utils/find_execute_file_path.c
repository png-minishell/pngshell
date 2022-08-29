/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_execute_file_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:07:36 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 19:36:40 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell_definitions.h"

static char	*get_excute_file_path(char *command, char **path)
{
	int		path_index;
	char	*excute_file;

	path_index = 0;
	while (path[path_index])
	{
		excute_file = ft_strjoin(path[path_index], command);
		if (check_permission(excute_file))
		{
			free(command);
			free_strings(path);
			return (excute_file);
		}
		free(excute_file);
		path_index++;
	}
	return (0);
}

int	check_builtin(const char *command_name)
{
	if (ft_strncmp("echo", command_name, -1) == 0)
		return (BT_ECHO);
	else if (ft_strncmp("cd", command_name, -1) == 0)
		return (BT_CD);
	else if (ft_strncmp("pwd", command_name, -1) == 0)
		return (BT_PWD);
	else if (ft_strncmp("export", command_name, -1) == 0)
		return (BT_EXPORT);
	else if (ft_strncmp("unset", command_name, -1) == 0)
		return (BT_UNSET);
	else if (ft_strncmp("env", command_name, -1) == 0)
		return (BT_ENV);
	else if (ft_strncmp("exit", command_name, -1) == 0)
		return (BT_EXIT);
	return (BT_NONE);
}

char	**get_paths(void)
{
	char	*value;
	char	**path;

	value = get_value("PATH", envp, 0);
	path = ft_split(value, ':');
	free(value);
	return (path);
}

char	*find_execute_file_path(char *command_name)
{
	int		path_index;
	char	**path;
	char	*command;
	char	*excute_file;

	path_index = 0;
	if (check_permission(command_name))
		return (ft_strdup(command_name));
	command = ft_strjoin("/", command_name);
	path = get_paths();
	excute_file = get_excute_file_path(command, path);
	if (!excute_file)
	{
		free(command);
		free_strings(path);
		return (0);
	}
	return (excute_file);
}
