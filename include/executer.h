/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:19:29 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 19:33:26 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <stddef.h>
# include "binary_tree.h"
# include "minishell_definitions.h"

size_t			get_number_of_pipe(t_btree_node *ast);
t_token_kind	get_node_token_kind(t_btree_node *node);
t_status		do_token_purpose(t_btree_node *noe, t_cmd *cmd);
t_status		do_command(t_btree_node *const left_leaf);
t_status		executer(t_btree_node *ast);

t_btree_node	*get_left_leaf(t_btree_node *const root);
t_btree_node	*get_next_root(t_btree_node *const left_leaf);

t_status		do_infile_redirection(const char *path);
t_status		do_outfile_redirection(const char *path, int flag, int mode);
t_status		do_heredoc_redirection(t_btree_node *const node);
#endif
