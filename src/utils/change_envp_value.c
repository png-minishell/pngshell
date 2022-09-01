/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_envp_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:43:18 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 16:57:37 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "libft.h"

int	get_envp_index(const char *key, char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(key, envp[index], ft_strlen(key)) == 0)
			return (index);
		index++;
	}
	return (index);
}

char	*get_string_of_env(const char *key, const char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**change_envp_value(const char *key, const char *value, char **envp)
{
	int	index;

	index = get_envp_index(key, envp);
	if (envp[index] != NULL)
	{
		free(envp[index]);
		envp[index] = get_string_of_env(key, value);
	}
	else
	{
		envp[index] = get_string_of_env(key, value);
		envp[++index] = NULL;
	}
	return (0);
}
