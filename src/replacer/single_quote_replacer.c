/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_replacer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:05:33 by parksungj         #+#    #+#             */
/*   Updated: 2022/09/02 14:57:19 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "replacer.h"
#include "libft.h"

static char	*get_single_quote_string(const char *str)
{
	char	*result;
	size_t	idx_str;
	size_t	idx_res;

	result = e_malloc(sizeof(char) * ft_strlen(str) * 2);
	idx_str = 1;
	idx_res = 0;
	while (str[idx_str] && str[idx_str] != '\'')
	{
		if (ft_isspace(str[idx_str]) || is_symbol(str[idx_str]))
		{
			result[idx_res++] = '\\';
		}
		result[idx_res++] = str[idx_str++];
	}
	result[idx_res] = 0;
	return (result);
}

static size_t	get_idx(const char *str)
{
	size_t	idx_str;

	idx_str = 1;
	while (str[idx_str] && str[idx_str] != '\'')
	{
		++idx_str;
	}
	return (idx_str);
}

void	single_quote_replacer(\
			const char *str, char *result, size_t *idx_str, size_t *idx_result)
{
	char	*single_quote_str;

	single_quote_str = get_single_quote_string(str);
	copy_string(single_quote_str, result, idx_result);
	*idx_str += get_idx(str);
	free(single_quote_str);
}
