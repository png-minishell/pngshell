/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:01:53 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/24 18:30:45 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "replacer.h"
#include "libft.h"

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
		else if (str[idx_str] == '$' && str[idx_str + 1])
			env_replacer(str + idx_str, res, &idx_str, &idx_res);
		else
			res[idx_res++] = str[idx_str];
		if (str[idx_str] == 0)
			break ;
		++idx_str;
	}
	res[idx_res] = 0;
}

char	*replacer(const char *str)
{
	char	*result_tmp;
	char	*result;

	result_tmp = e_malloc(sizeof(char) * (get_replaced_string_size(str)));
	scan_and_replace(str, result_tmp);
	result = ft_strdup(result_tmp);
	free(result_tmp);
	return (result);
}
