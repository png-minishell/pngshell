/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_definitions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:28:59 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 17:34:34 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINITIONS_H
# define MINISHELL_DEFINITIONS_H

# define FAILED -1
# define SUCCESS 0
typedef int t_status;

# define FALSE 0
# define TRUE 1
typedef int t_bool;

typedef enum e_token_kind
{
	TK_ARG = 0,
	TK_ARG_DOUBLE_QUOTE = 0,
	TK_FILE_PATH = 1,
	TK_CMD = 1,
	TK_LESS = 2,
	TK_GREATER = 2,
	TK_DOUBLE_LESS = 2,
	TK_DOUBLE_GREATER = 2,
	TK_PIPE = 5,
	TK_ERROR = -1,
	TK_ARR_END = -128,
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

typedef struct s_cmd
{
	char	*cmd_string;
	char	**arguments;
}	t_cmd;

#endif
