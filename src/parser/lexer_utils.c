/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:23:46 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 14:49:28 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "error_control_functions.h"
#include "lexer.h"
#include "libft.h"

/*
 *	t_tokenized_string list sturcture :
 *		lst [ content : t_tokenized_string * ]
 * */
t_tokenized_string *lst_to_arr(t_list *head)
{
	const size_t		lst_size = ft_lstsize(head);
	t_tokenized_string	*arr;
	size_t				idx;
	t_list				*node;

	arr = e_malloc(sizeof(t_tokenized_string *) * (lst_size + 1));
	idx = 0;
	node = head;
	while (node)
	{
		arr[idx] = *((t_tokenized_string *)(node->content));
		node = node->next;
		++idx;
	}
	arr[idx].kind = TK_ARR_END;
	return (arr);
}

t_token_status	get_status(\
		const t_token_status prev_status, const char *str, const size_t index)
{
	if ((prev_status == ST_SINGLE_QUOTE && ft_strncmp("'", str + index, 1))
		|| (prev_status == ST_DOUBLE_QUOTE && ft_strncmp("\'", str + index, 1)))
		return (ST_ERROR);
	if (ft_strncmp("<<", str + index, 2) == 0)
		return (ST_DOUBLE_LESS);
	if (ft_strncmp(">>", str + index, 2) == 0)
		return (ST_DOUBLE_GREATER);
	if (str[index] == '<')
		return (ST_LESS);
	if (str[index] == '>')
		return (ST_GREATER);
	if (str[index] == '|')
		return (ST_PIPE);
	if (str[index] == '\"')
		return (ST_DOUBLE_QUOTE);
	if (str[index] == '\'')
		return (ST_SINGLE_QUOTE);
	if (prev_status == ST_DOUBLE_GREATER || prev_status == ST_DOUBLE_LESS
		|| prev_status == ST_GREATER || prev_status == ST_LESS)
		return (ST_FILE_PATH);
	if (prev_status == ST_CMD || prev_status == ST_ARG)
		return (ST_ARG);
	return (ST_CMD);
}

t_token_kind	get_token_kind(const t_token_status status)
{
	if (status == ST_LESS)
		return (TK_LESS);
	if (status == ST_GREATER)
		return (TK_GREATER);
	if (status == ST_DOUBLE_LESS)
		return (TK_DOUBLE_LESS);
	if (status == ST_DOUBLE_GREATER)
		return (TK_DOUBLE_GREATER);
	if (status == ST_PIPE)
		return (TK_PIPE);
	if (status == ST_SINGLE_QUOTE)
		return (TK_ARG);
	if (status == ST_CMD)
		return (TK_CMD);
	if (status == ST_FILE_PATH)
		return (TK_FILE_PATH);
	if (status == ST_DOUBLE_QUOTE)
		return (TK_ARG_DOUBLE_QUOTE);
	if (status == ST_ARG)
		return (TK_ARG);
	return (TK_ERROR);
}

t_tokenized_string	*get_new_token(char *str, const t_token_status status)
{
	t_tokenized_string	*new_token;

	new_token = e_malloc(sizeof(t_tokenized_string));
	new_token->kind = get_token_kind(status);
	new_token->str = str;
	return (new_token);
}
