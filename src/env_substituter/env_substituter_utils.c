/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substituter_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:38:29 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 00:11:10 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	free_strings_array(char **arr)
{
	size_t	index;

	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		++index;
	}
	free(arr);
	return ;
}

static char	*find_key_and_get_value(const char *key, char **envp)
{
	char	**strs;
	char	*value;
	size_t	index;

	index = 0;
	while (envp[index])
	{
		strs = ft_split(envp[index], '=');
		if (ft_strncmp(strs[0], key, -1) == 0)
		{
			value = ft_strdup(strs[1]);
			free_strings_array(strs);
			return (value);
		}
		free_strings_array(strs);
		++index;
	}
	return (NULL);
}

char	*get_value(const char *key, char **envp, char **set)
{
	size_t	index;
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
	while (str[index] && !ft_isspace(str[index]) && str[index] != '$')
	{
		++index;
	}
	return (ft_substr(str + 1, 0, index - 1));
}

