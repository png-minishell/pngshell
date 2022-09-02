/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:26:49 by sungjpar          #+#    #+#             */
/*   Updated: 2022/09/02 13:38:48 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_definitions.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"

void	put_not_valid_identifier_err(char *err)
{
	ft_putstr_fd("shell: export: `", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
	errno = 1;
}

t_bool	is_valid_key(const char *key)
{
	const char	*invalid_chars = "\\/:*?\"<>|";
	size_t		idx;

	if (ft_isdigit(key[0]))
		return (FALSE);
	idx = 0;
	while (key[idx] && key[idx] != '=')
	{
		if (ft_isinset(key[idx], invalid_chars))
			return (FALSE);
		++idx;
	}
	return (TRUE);
}

static char	*get_key_from_string(const char *str)
{
	return (ft_substr(str, 0, ft_strchr(str, '=') - str));
}

static char	*get_value_from_string(char **args, int *idx_arg)
{
	char	*value;

	value = ft_strchr(args[*idx_arg], '=');
	if (value && *(value + 1))
		value = ft_strdup(value + 1);
	else if (args[*idx_arg + 1] && !ft_strchr(args[*idx_arg + 1], '='))
		value = ft_strdup(args[++(*idx_arg)]);
	else
		value = ft_strdup("");
	return (value);
}

void	exporting_envp(char **args, char **envp)
{
	int		idx_arg;
	char	*key;
	char	*value;

	idx_arg = 1;
	while (args[idx_arg])
	{
		key = get_key_from_string(args[idx_arg]);
		if (!is_valid_key(key))
		{
			put_not_valid_identifier_err(args[idx_arg]);
			++idx_arg;
			continue ;
		}
		value = get_value_from_string(args, &idx_arg);
		if (value)
		{
			change_envp_value(key, value, envp);
			free(value);
		}
		++idx_arg;
		free(key);
	}
}
