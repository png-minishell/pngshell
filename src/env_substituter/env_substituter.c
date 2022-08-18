/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substituter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:32:46 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/18 18:09:44 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error_control_functions.h"

static void	free_strings_array(char **arr)
{
	size_t	index;

	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		++index;
	}
	free(arr[index]);
	return ;
}

char	*get_value(const char *key, char **envp)
{
	size_t	index;
	char	**strs;
	char	*value;

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
	return (ft_strdup(""));
}

char	*get_key(const char *str)
{
	size_t	index;

	index = 1;
	while (!ft_isspace(str[index]) && str[index] != '$')
	{
		++index;
	}
	return (ft_substr(str + 1, 0, index - 1));
}

static size_t	get_replaced_length(const char *str, char **envp)
{
	size_t	length;
	size_t	index;
	char	*key;
	char	*value;

	length = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1])
		{
			key = get_key(str + index);
			value = get_value(key, envp);
			length -= ft_strlen(key) + 1;
			length += ft_strlen(value);
			index += ft_strlen(key);
			free(key);
			free(value);
		}
		else
			++length;
		++index;
	}
	return (length);
}

char	*env_substituter(const char *str, char **envp)
{
	char	*result_string;
	char	*key;
	char	*value;
	size_t	index;
	size_t	r_index;

	index = 0;
	r_index = 0;
	result_string = e_malloc(get_replaced_length(str, envp) + 1);
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1])
		{
			key = get_key(str + index);
			value = get_value(key, envp);
			ft_strlcpy(result_string + r_index, value, ft_strlen(value) + 1);
			r_index += ft_strlen(value);
			index += ft_strlen(key);
			free(key);
			free(value);
		}
		else
			result_string[r_index++] = str[index];
		++index;
	}
	result_string[r_index] = 0;
	return (result_string);
}
