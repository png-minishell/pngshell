/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:01:53 by sungjpar          #+#    #+#             */
/*   Updated: 2022/09/02 15:55:16 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "replacer.h"
#include "libft.h"

static t_bool	is_quote(const char c)
{
	return (c == '\'' || c == '"');
}

static char	*replace_env(const char *str)
{
	char	*res;
	size_t	idx_str;
	size_t	idx_res;

	idx_str = 0;
	idx_res = 0;
	res = e_malloc(sizeof(char) * get_replaced_string_size(str));
	while (str[idx_str])
	{
		if (str[idx_str] == '\'')
			single_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else if (str[idx_str] == '$' && is_quote(str[idx_str + 1]))
			res[idx_res++] = str[idx_str];
		else if (str[idx_str] == '$' && str[idx_str + 1] == '$')
			++idx_str;
		else if (str[idx_str] == '$' && str[idx_str + 1])
			env_replacer(str + idx_str, res, &idx_str, &idx_res);
		else
			res[idx_res++] = str[idx_str];
		if (str[idx_str++] == 0)
			break ;
	}
	res[idx_res] = 0;
	return (res);
}

static void	scan_and_replace(\
		const char *str, char *res)
{
	size_t	idx_str;
	size_t	idx_res;

	idx_str = 0;
	idx_res = 0;
	while (str[idx_str])
	{
		if (str[idx_str] == '\\' && !is_symbol(str[idx_str + 1]))
			res[idx_res++] = str[++idx_str];
		else if (str[idx_str] == '\'')
			single_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else if (str[idx_str] == '"')
			double_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else
			res[idx_res++] = str[idx_str];
		if (str[idx_str++] == 0)
			break ;
	}
	res[idx_res] = 0;
}

char	*replacer(const char *str)
{
	char	*env_replaced_str;
	char	*result;

	env_replaced_str = replace_env(str);
	result = e_malloc(sizeof(char) * ft_strlen(env_replaced_str) * 2);
	scan_and_replace(env_replaced_str, result);
	free(env_replaced_str);
	return (result);
}
