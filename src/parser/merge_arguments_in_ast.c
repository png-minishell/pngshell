/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arguments_in_ast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:11:54 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/23 18:52:10 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "parser.h"
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
	char	*path;

	if (root == NULL)
		return ;
	token = root->content;
	if (token->kind == TK_CMD)
	{
		path = find_execute_file_path(token->str);
		if (path == NULL)
			path = ft_strdup("");
		free(token->str);
		token->str = path;
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
