/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:55:15 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/18 14:43:49 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell_definitions.h"
# include "binary_tree.h"

t_token			*create_malloced_token(t_token token);
t_token_type	get_token_type(t_token token);
int				cmp_kind(t_token token1, t_token token2);;
t_btree_node	*find_node_position(\
					t_btree_node *current_node,
					t_btree_node *node);
t_btree_node	*create_token_ast_from_tokens(t_token *tokens);
t_btree_node	*parser(const char *str);

#endif
