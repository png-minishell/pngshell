/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:19:29 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/22 15:20:13 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <stddef.h>
# include "binary_tree.h"
# include "minishell_definitions.h"
# define PIPE_INDEX_READ 0
# define PIPE_INDEX_WRITE 1

size_t			get_number_of_pipe(t_btree_node *ast);
t_token_kind	get_node_token_kind(t_btree_node *node);
t_status		do_token_purpose(t_btree_node *noe, t_cmd *cmd);
t_status		execute_commands_from_ast(t_btree_node *ast);
t_status		set_pipe(int no_cmd, int number_of_cmds, int pipelines[2][2]);

t_btree_node	*get_left_leaf(t_btree_node *const root);
t_btree_node	*get_next_root(t_btree_node *const left_leaf);

t_status		do_infile_redirection(const char *path);
t_status		do_outfile_redirection(const char *path, int flag, int mode);
t_status		do_heredoc_redirection(void);
#endif
