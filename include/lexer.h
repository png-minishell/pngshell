/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:16:22 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 14:52:51 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "minishell_definitions.h"

# define SYMBOLS "$()<>|&\'\"\\*"

typedef enum e_token_kind
{
	TK_DOLLAR = '$',
	TK_LESS = '<',
	TK_GREATER = '>',
	TK_PIPE = '|',
	TK_SINGLE_QUOTE = '\'',
	TK_DOUBLE_QUOTE = '\"',
	TK_ARG = 'a',
	TK_ARG_DOUBLE_QUOTE = 'd',
	TK_CMD = 'c',
	TK_DOUBLE_LESS = 'l',
	TK_DOUBLE_GREATER = 'g',
	TK_ERROR = -1,
	TK_ARR_END = -128,
	TK_FILE_PATH = 'f'
}	t_token_kind;

typedef enum e_token_status
{
	ST_START,
	ST_CMD,
	ST_ARG,
	ST_DOLLAR,
	ST_SINGLE_QUOTE,
	ST_DOUBLE_QUOTE,
	ST_DOUBLE_LESS,
	ST_DOUBLE_GREATER,
	ST_PIPE,
	ST_LESS,
	ST_GREATER,
	ST_ESCAPE,
	ST_PAREN,
	ST_BRACKET,
	ST_BRACE,
	ST_FILE_PATH,
	ST_EOF,
	ST_ERROR = -1
}	t_token_status;

typedef struct s_tokenized_string
{
	char			*str;
	t_token_kind	kind;
}	t_tokenized_string;

t_tokenized_string	*lexer(const char *str);
t_status			tokenize_string(const char *str, t_list **token_list);

/* LEXER UTILS */
t_tokenized_string	*lst_to_arr(t_list *head);
size_t				get_word_end_index(\
						const char *str,
						const size_t start_index,
						const t_token_status status);
t_token_status		get_status(\
						const t_token_status prev_status,
						const char *str,
						const size_t index);
t_token_kind		get_token_kind(const t_token_status status);
t_tokenized_string	*get_new_token(char *str, const t_token_status status);
size_t				skip_space(const char *str, size_t start_index);
size_t				skip_word(const char *str, size_t start_index);
size_t				skip_until_quote(\
						const char *str,
						const size_t start_index,
						const t_token_status status);
#endif
