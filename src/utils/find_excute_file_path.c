/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_excute_file_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:07:36 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/21 17:07:47 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_definitions.h"

char	*find_excute_file_path(char *command_name, char **envp)
{
	int		path_index;
	char	**path;
	char	*command;
	char	*excute_file;

	path_index = 0;
	command =ft_strjoin("/", command_name);
	path = ft_split(get_value("PATH", envp, 0), ':');
	while (path[path_index])
	{
		excute_file =ft_strjoin(path[path_index], command);
		if (check_permission(excute_file))
			return (excute_file);
		path_index++;
	}
	return (0);
}
