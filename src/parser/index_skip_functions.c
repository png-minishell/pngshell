/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_skip_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:17:40 by parksungj         #+#    #+#             */
/*   Updated: 2022/09/02 17:24:54 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "lexer.h"
#include "libft.h"

size_t	skip_space(const char *str, size_t start_index)
{
	size_t	result_index;

	result_index = start_index;
	while (ft_isspace(str[result_index]))
	{
		++result_index;
	}
	return (result_index);
}

size_t	skip_word(const char *str, size_t start_index)
{
	size_t	index;

	index = start_index;
	while (str[index] && !ft_isspace(str[index]))
	{
		if (str[index] == '\\' && ft_isspace(str[index + 1]))
			++index;
		++index;
	}
	return (index);
}

size_t	get_word_end_index(\
		const char *str, const size_t start_index, const t_status status)
{
	if (status == ST_LESS || status == ST_GREATER)
		return (start_index);
	else if (status == ST_DOUBLE_GREATER || status == ST_DOUBLE_LESS)
		return (start_index + 1);
	else if (status == ST_PIPE)
		return (start_index);
	else
		return (skip_word(str, start_index));
}
