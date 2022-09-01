/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:01:53 by sungjpar          #+#    #+#             */
/*   Updated: 2022/09/01 19:03:18 by sungjpar         ###   ########.fr       */
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

static char	*replace_double_double_quote(const char *str)
{
	char	*result;
	size_t	idx_str;
	size_t	idx_res;

	idx_str = 0;
	idx_res = 0;
	result = e_malloc(sizeof(char) * ft_strlen(str));
	while (str[idx_str])
	{
		if (ft_strncmp(str + idx_str, "\"\"", 2) == 0)
		{
			idx_str += 2;
			continue ;
		}
		if (ft_strncmp(str + idx_str, "\\\"", 2) == 0)
		{
			result[idx_res++] = str[idx_str++];
			result[idx_res++] = str[idx_str++];
			continue ;
		}
		result[idx_res++] = str[idx_str++];
	}
	result[idx_res] = 0;
	return (result);
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
		if (str[idx_str] == '\\')
			res[idx_res++] = str[++idx_str];
		else if (str[idx_str] == '\'')
			single_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else if (str[idx_str] == '"')
			double_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else if (str[idx_str] == '$' && is_quote(str[idx_str + 1]))
			;
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
}

char	*replacer(const char *str)
{
	char	*result_tmp;
	char	*result;

	result = e_malloc(sizeof(char) * (get_replaced_string_size(str)));
	result_tmp = replace_double_double_quote(str);
	scan_and_replace(result_tmp, result);
	free(result_tmp);
	return (result);
}
