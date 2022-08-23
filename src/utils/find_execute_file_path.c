/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_execute_file_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:07:36 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/22 21:30:11 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell_definitions.h"

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
	command = ft_strjoin("/", command_name);
	path = get_paths();
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
	free(command);
	free_strings(path);
	return (0);
}
