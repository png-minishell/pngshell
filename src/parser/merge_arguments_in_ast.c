/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arguments_in_ast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:11:54 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:21:11 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "parser.h"
#include "replacer.h"
#include "libft.h"

size_t	get_number_of_arguments(t_btree_node *cmd_node)
{
	size_t			num;
	t_btree_node	*node;

	num = 0;
	node = cmd_node->right_child;
	while (node)
	{
		++num;
		node = node->right_child;
	}
	return (num);
}

char	*double_quote_string_to_word(const char *str)
{
	char	*replaced_str;
	size_t	idx_str;
	size_t	idx_res;

	idx_str = 0;
	idx_res = 0;
	replaced_str = e_malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[idx_str])
	{
		if (str[idx_str] == '\\')
			replaced_str[idx_res] = replace_backslash(str + idx_str, &idx_str);
		else
			replaced_str[idx_res] = str[idx_str];
		++idx_res;
		if (str[idx_str++] == 0)
			break ;
	}
	replaced_str[idx_res] = 0;
	return (replaced_str);
}

char	**get_arguments(t_btree_node *cmd_node)
{
	const size_t	number_of_arguments = get_number_of_arguments(cmd_node);
	char			**argv;
	t_btree_node	*node;
	t_token			*token;
	size_t			index;

	node = cmd_node;
	index = 0;
	argv = e_malloc(sizeof(char *) * (number_of_arguments + 2));
	while (node)
	{
		token = node->content;
		if (token->kind == TK_WORD_DOUBLE_QUOTE)
			argv[index] = double_quote_string_to_word(token->str);
		else
			argv[index] = ft_strdup(token->str);
		node = node->right_child;
		++index;
	}
	argv[index] = NULL;
	return (argv);
}

void	find_cmd_and_merge_arguments(t_btree_node *root)
{
	t_token	*token;

	if (root == NULL)
		return ;
	token = root->content;
	if (token->kind == TK_CMD)
	{
		token->arguments = get_arguments(root);
		if (root->right_child)
			bst_clear_tree(root->right_child, free_token);
		root->right_child = NULL;
		return ;
	}
	find_cmd_and_merge_arguments(root->left_child);
	find_cmd_and_merge_arguments(root->right_child);
}

t_btree_node	*merge_arguments_in_ast(t_btree_node *ast)
{
	find_cmd_and_merge_arguments(ast);
	return (ast);
}
