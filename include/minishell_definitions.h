/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_definitions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:27:21 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/24 20:00:13 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINITIONS_H
# define MINISHELL_DEFINITIONS_H

# include <sys/stat.h>
# include "binary_tree.h"

# define FAILED -1
# define SUCCESS 0

typedef int	t_status;

# define FALSE 0
# define TRUE 1

typedef int	t_bool;

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
	ST_ERROR = 127,
	ST_END = 126,
}	t_token_status;

typedef struct s_token
{
	char			*str;
	char			**arguments;
	t_token_kind	kind;
	int				pipe_fd;
}	t_token;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
}	t_cmd;

extern char	**envp;
extern char	**set;
extern int	stdin_bak;
extern int	stdout_bak;

char			*get_value(const char *key, char **envp, char **set);
char			*get_key(const char *str);
char			*env_substituter(const char *str, char **envp, char **set);
char			*replacer(const char *str);
t_btree_node	*create_ast_tree_from_string(const char *str);
int				heredoc(const char *limiter);
void			run_heredoc(t_btree_node *ast);
t_status		execute_commands_from_ast(t_btree_node *ast);
int				what_is_this_file(char *file, struct stat *file_buf);
int				check_permission(char *absolute_path);
char			*find_execute_file_path(char *command_name);
void			free_strings(char **strings);
void			free_token(void *ptr);
t_status		check_valid_ast(t_btree_node *ast);\
t_bool			is_symbol(const char c);

# define HEREDOC_FILE_NAME ".heredoc.tmp"
# define SYMBOLS "$<>|\'\"\\"

/* FILE TYPE DEFINE */
# define TYPE_FIFO		0
# define TYPE_CHR		1
# define TYPE_DIRECTORY	2
# define TYPE_BLOCK		3
# define TYPE_REGULAR	4
# define TYPE_LINK		5
# define TYPE_SOCKET	6
#endif
