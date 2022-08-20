/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substituter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:32:46 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 00:10:08 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error_control_functions.h"
#include "minishell_definitions.h"

static size_t	get_replaced_length(const char *str, char **envp, char **set)
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
			value = get_value(key, envp, set);
			length += ft_strlen(value);
			index += ft_strlen(key);
			free(key);
			free(value);
		}
		else
			++length;
		++index;
	}
	return (length + ft_strlen(str));
}

size_t	replace_env(\
			const char *str, char *result_string, size_t *r_index)
{
	char	*key;
	char	*value;
	size_t	len;

	key = get_key(str);
	value = get_value(key, envp, set);
	ft_strlcpy(result_string + *r_index, value, ft_strlen(value) + 1);
	*r_index += ft_strlen(value);
	len = ft_strlen(key);
	free(key);
	free(value);
	return (len);
}

char	*env_substituter(const char *str, char **envp, char **set)
{
	char	*result_string;
	size_t	r_index;
	size_t	index;

	r_index = 0;
	index = 0;
	result_string = e_malloc(get_replaced_length(str, envp, set) + 1);
	while (str[index])
	{
		if (str[index] == '$'
			&& str[index + 1]
			&& (!index || str[index - 1] != '\\'))
		{
			index += replace_env(str, result_string, &r_index);
		}
		else
			result_string[r_index++] = str[index];
		++index;
	}
	result_string[r_index] = 0;
	return (result_string);
}

/*
#include <stdio.h>
int	main(void)
{
	char *tc = "test1 '$HOME' \\$HOME $HOME";
	char *env[] = {
		"HOME=test",
		NULL
	};
	char *set[] = {
		"set=OO",
		NULL
	};
	
	printf("%s", env_substituter(tc, env, set));
}
*/
