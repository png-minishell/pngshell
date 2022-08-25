/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:19:29 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:18:14 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <stddef.h>
# include <unistd.h>
# include "binary_tree.h"
# include "minishell_definitions.h"
# define PIPE_INDEX_READ 0
# define PIPE_INDEX_WRITE 1

size_t			get_number_of_pipe(t_btree_node *ast);
t_token_kind	get_node_token_kind(t_btree_node *node);
t_status		do_token_purpose(t_btree_node *node);
t_status		execute_commands_from_ast(t_btree_node *ast);
t_status		set_pipe(int no_cmd, int number_of_cmds, int pipelines[2][2]);
t_status		analyze_and_execute_command(t_btree_node *const left_leaf);
t_status		run_command(t_token *cmd_token);
t_btree_node	*get_left_leaf(t_btree_node *const root);
t_btree_node	*get_next_root(t_btree_node *const left_leaf);

t_status		do_infile_redirection(const char *path);
t_status		do_outfile_redirection(const char *path, int flag, int mode);
t_status		do_heredoc_redirection(const int fd);

void			explore_tree_and_execute_command(\
					t_btree_node *ast,
					pid_t *pid, const size_t number_of_process);

#endif
