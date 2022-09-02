/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:04:12 by parksungj         #+#    #+#             */
/*   Updated: 2022/09/02 16:04:23 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "error_control_functions.h"
#include "minishell_definitions.h"

static int	pass_operator_index(t_token_status status)
{
	if (status == ST_LESS
		|| status == ST_GREATER
		|| status == ST_PIPE
		|| status == ST_DOUBLE_QUOTE
		|| status == ST_SINGLE_QUOTE)
		return (1);
	else if (status == ST_DOUBLE_LESS
		|| status == ST_DOUBLE_GREATER)
		return (2);
	else
		return (0);
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

static char	*remove_backslash(char *word)
{
	char	*new_word;
	size_t	idx_word;
	size_t	idx_new_word;

	new_word = e_malloc(sizeof(char) * ft_strlen(word) + 1);
	idx_word = 0;
	idx_new_word = 0;
	while (word[idx_word])
	{
		if (word[idx_word] == '\\')
			++idx_word;
		new_word[idx_new_word++] = word[idx_word++];
	}
	new_word[idx_new_word] = 0;
	free(word);
	return (new_word);
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
		current_index = get_word_end_index(str, start_index);
		word = ft_substr(str, start_index, current_index - start_index);
		word = remove_backslash(word);
		ft_lstadd_back(token_list, ft_lstnew(get_new_token(word, status)));
		if (str[current_index] == '\0')
			break ;
		current_index += pass_operator_index(status);
	}
	if (*token_list == NULL)
		ft_lstadd_back(token_list, \
				ft_lstnew(get_new_token(ft_strdup(str), ST_ARG)));
	return (SUCCESS);
}
