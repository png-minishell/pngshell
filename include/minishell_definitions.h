/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_definitions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:28:59 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 22:01:17 by sungjpar         ###   ########.fr       */
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

typedef enum e_token_type
{
	TYPE_WORD = 0,
	TYPE_CMD = 1,
	TYPE_REDIRECT = 2,
	TYPE_PIPE = 5,
	TYPE_ERROR = 127
}	t_token_type;

typedef enum e_token_kind
{
	TK_WORD = 0,
	TK_WORD_DOUBLE_QUOTE = 1,
	TK_CMD = 2,
	TK_LESS = 3,
	TK_GREATER = 4,
	TK_DOUBLE_LESS = 5,
	TK_DOUBLE_GREATER = 6,
	TK_PIPE = 7,
	TK_ERROR = 10,
	TK_ARR_END = 11,
}	t_token_kind;

typedef enum e_token_status
{
	ST_END = 126,
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
	ST_ERROR = 127
}	t_token_status;

typedef struct s_token
{
	char			*str;
	t_token_kind	kind;
}	t_token;

typedef struct s_cmd
{
	char	*cmd_string;
	char	**arguments;
}	t_cmd;

#endif