/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:04:12 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 20:46:52 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "error_control_functions.h"

static t_bool	is_double_operator(t_token_status status)
{
	return (status == ST_DOUBLE_LESS || status == ST_DOUBLE_GREATER);
}

t_token	*lexer(const char *str)
{
	t_token	*result;
	t_list	*token_list;

	token_list = NULL;
	tokenize_string(str, &token_list);
	result = lst_to_arr(token_list);
	ft_lstclear(&token_list, free);
	return (result);
}

t_status	tokenize_string(const char *str, t_list **token_list)
{
	size_t				start_index;
	size_t				current_index;
	char				*word;
	t_token_status		status;

	current_index = 0;
	status = ST_START;
	while (str[current_index])
	{
		start_index = skip_space(str, current_index);
		if (str[start_index] == '\0')
			break ;
		status = get_status(status, str, start_index);
		start_index += (status == ST_DOUBLE_QUOTE || status == ST_SINGLE_QUOTE);
		current_index = get_word_end_index(str, start_index, status);
		word = ft_substr(str, start_index, current_index - start_index);
		ft_lstadd_back(token_list, ft_lstnew(get_new_token(word, status)));
		if (str[current_index] == '\0')
			break ;
		++current_index;
		current_index += is_double_operator(status);
	}
	return (SUCCESS);
}

