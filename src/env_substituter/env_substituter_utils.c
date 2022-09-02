/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substituter_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:38:29 by sungjpar          #+#    #+#             */
/*   Updated: 2022/09/02 16:00:10 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell_definitions.h"

static char	*find_key_and_get_value(const char *key, char **envp)
{
	char	**strs;
	char	*value;
	size_t	index;

	index = 0;
	if (key == NULL || envp == NULL)
		return (NULL);
	while (envp[index])
	{
		strs = ft_split(envp[index], '=');
		if (strs[0] == NULL)
		{
			++index;
			continue ;
		}
		if (ft_strncmp(strs[0], key, -1) == 0 && strs[1])
		{
			value = ft_strdup(strs[1]);
			free_strings(strs);
			return (value);
		}
		free_strings(strs);
		++index;
	}
	return (NULL);
}

char	*get_value(const char *key, char **envp, char **set)
{
	char	*value;

	value = find_key_and_get_value(key, envp);
	if (value == NULL)
		value = find_key_and_get_value(key, set);
	if (value == NULL)
		return (ft_strdup(""));
	else
		return (value);
}

char	*get_key(const char *str)
{
	size_t	index;

	index = 1;
	while (str[index]
		&& !ft_isspace(str[index])
		&& str[index] != '='
		&& !is_symbol(str[index]))
	{
		++index;
	}
	return (ft_substr(str + 1, 0, index - 1));
}
