/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:16:22 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 20:13:25 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "minishell_definitions.h"

# define SYMBOLS "$()<>|&\'\"\\*"

/* Main lexer functions */
t_token				*lexer(const char *str);
t_status			tokenize_string(const char *str, t_list **token_list);

/* LEXER UTILS */
t_token				*lst_to_arr(t_list *head);
size_t				get_word_end_index(\
						const char *str,
						const size_t start_index,
						const t_token_status status);
t_token_status		get_status(\
						const t_token_status prev_status,
						const char *str,
						const size_t index);
t_token_kind		get_token_kind(const t_token_status status);
t_token				*get_new_token(char *str, const t_token_status status);

/* index skip functions */
size_t				skip_space(const char *str, size_t start_index);
size_t				skip_word(const char *str, size_t start_index);
size_t				skip_until_quote(\
						const char *str,
						const size_t start_index,
						const t_token_status status);
#endif
