/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_definitions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:27:21 by sungjpar          #+#    #+#             */
/*   Updated: 2022/09/02 18:30:29 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINITIONS_H
# define MINISHELL_DEFINITIONS_H

# include <stddef.h>
# include <sys/stat.h>
# include "binary_tree.h"

# define SYMBOLS "$<>|\'\"\\"

# define FAILED -1
# define SUCCESS 0

typedef int					t_status;

# define FALSE 0
# define TRUE 1

typedef int					t_bool;

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

typedef enum e_builtin_kind
{
	BT_NONE = 0,
	BT_ECHO,
	BT_CD,
	BT_PWD,
	BT_EXPORT,
	BT_UNSET,
	BT_ENV,
	BT_EXIT,
}	t_builtin_kind;

typedef struct s_token
{
	char			*str;
	char			**arguments;
	t_token_kind	kind;
	int				pipe_fd;
}	t_token;
/* FILE TYPE DEFINE */
typedef enum e_file_types
{
	TYPE_FIFO = -128,
	TYPE_CHR,
	TYPE_DIRECTORY,
	TYPE_BLOCK,
	TYPE_REGULAR,
	TYPE_LINK,
	TYPE_SOCKET,
}	t_file_types;

typedef struct s_program_variables
{
	char	**envp;
	char	**set;
	char	*cwd;
	int		stdin_bak;
	int		stdout_bak;
	int		exit_code;
}	t_program_variables;

extern t_program_variables	g_vars;

char			*get_value(const char *key, char **envp, char **set);
char			*get_key(const char *str);
char			*env_substituter(const char *str, char **envp, char **set);
char			**change_envp_value(\
					const char *key, const char *value, char **envp);
char			*replacer(const char *str);
t_btree_node	*create_ast_tree_from_string(const char *str);
int				heredoc(const char *limiter);
void			run_heredoc(t_btree_node *ast);
t_status		execute_commands_from_ast(t_btree_node *ast);
int				get_file_type(char *file, struct stat *file_buf);
int				check_permission(char *absolute_path);
char			*find_execute_file_path(char *command_name);
void			free_strings(char **strings);
void			free_token(void *ptr);
t_status		check_valid_ast(t_btree_node *ast);
t_bool			is_symbol(const char c);
int				check_builtin(const char *command_name);
int				get_envp_index(const char *key, char **envp);
void			prompt(void);
void			print_main_page(void);
/* BULITIN FUNCTIONS */
int				builtin_cd(char **arguments, char **envp);
int				builtin_env(char **envp);
int				builtin_exit(char **arguments);
int				builtin_export(char **arguments, char **envp);
int				builtin_pwd(void);
int				builtin_unset(char **arguments, char **envp);

void			sigint_handler(int signum);
void			child_sig_handler(int signum);
size_t			get_number_of_arguments(t_btree_node *cmd_node);
t_bool			has_space(const char *str);
#endif
