/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_excute_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:25:55 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/21 16:25:57 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "libft.h"

char	*find_filepath(char *command_name, char **envp)
{
	int		path_index;
	char	**path;
	char	*command;
	char	*excute_file;

	path_index = 0;
	path = ft_split(get_value("PATH", envp, 0), ':');
	while (path[path_index])
	{
		excute_file =ft_strjoin(path[i], command_name);
		if (check_permission(excute_file))
			return (excute_file);
		path_index++;
	}
	return (0);
}
