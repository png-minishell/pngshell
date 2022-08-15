/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:04:12 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/16 01:10:36 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "error_control_functions.h"

t_tokenized_string	*lexer(const char *str)
{
	t_tokenized_string	*result;
	t_list				*token_list;

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
	status =-ST_START;
	while (str[current_index])
	{
		start_index = skip_space(str, current_index);
		if (str[start_index] == '\0')
			break ;
		status = get_status(status, str, start_index); 
		/* FIX !!
		if (status == ST_ERROR)
			invalid_token_error();
			
		*/
		current_index = get_word_end_index(str, start_index, status);
		word = ft_substr(str, start_index, current_index - start_index);	
		ft_lstadd_back(token_list, ft_lstnew(get_new_token(word, status)));
		if (str[current_index] == '\0')
			break ;
		++current_index;
		current_index += (status == ST_DOUBLE_LESS || status == ST_DOUBLE_GREATER);
	}
	return (SUCCESS);
}

int main(void)
{
	t_tokenized_string	*result;
	size_t				index = 0;

	result = lexer("cmd1 arg1 < file1 | cmd2 arg1 arg2 >> file2 | cmd3 >> file3 > filetest4");
	while (result[index].kind != TK_ARR_END)
	{
		printf("token : %s, kind : %c\n", result[index].str, result[index].kind); 
		++index;
	}
}
