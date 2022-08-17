/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:54:59 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 23:39:28 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stddef.h>
#include "lexer.h"
#include "binary_tree.h"
#include "minishell_definitions.h"
#include "error_control_functions.h"

static t_token	*create_malloced_token(t_token token)
{
	t_token	*new_token;

	new_token = e_malloc(sizeof(t_token));
	new_token->str = token.str;
	new_token->kind = token.kind;
	return (new_token);
}

t_token_type get_token_type(t_token token)
{
	const t_token_kind	kind = token.kind;

	if (kind == TK_WORD || kind == TK_WORD_DOUBLE_QUOTE)
		return (TYPE_WORD);
	if (kind == TK_LESS || kind == TK_DOUBLE_LESS
		|| kind == TK_GREATER || kind == TK_DOUBLE_GREATER)
		return (TYPE_REDIRECT);
	if (kind == TK_CMD)
		return (TYPE_CMD);
	if (kind == TK_PIPE)
		return (TYPE_PIPE);
	return (TYPE_ERROR);
}

int	cmp_kind(t_token token1, t_token token2)
{
	const t_token_type type1 = get_token_type(token1);
	const t_token_type type2 = get_token_type(token2);

	return (type1 - type2);
}

static t_btree_node	*find_node_position(\
		t_btree_node *current_node, t_btree_node *node)
{
	t_token	*current_node_token;
	t_token	*target_node_token;

	current_node_token = current_node->content;
	target_node_token = node->content;
	while (current_node->parent
		&& cmp_kind(*current_node_token, *target_node_token) < 0)
	{
		current_node = current_node->parent;
		current_node_token = current_node->content;
	}
	if (target_node_token->kind == TK_CMD)
	{
		while (current_node->left_child)
			current_node = current_node->left_child;
	}
	return (current_node);
}

/* CREATE AST FROM TOKENS*/
t_btree_node	*create_token_ast_from_tokens(t_token *tokens)
{
	t_btree_node	*current_node;
	t_btree_node	*new_node;
	t_token			*current_node_token;
	size_t			index;

	index = 0;
	current_node = NULL;
	while (tokens[index].kind != TK_ARR_END)
	{
		new_node = bst_create_node(create_malloced_token(tokens[index]));
		printf("index : %ld string : %s, kind :%d\n", index, ((t_token*)(new_node->content))->str, ((t_token *)new_node->content)->kind);
		if (current_node != NULL)
		{
			current_node_token = (t_token *)current_node->content;
			if (cmp_kind(*current_node_token, tokens[index]) >= 0)
				bst_link_right_child(current_node, new_node);
			else
			{
				current_node = find_node_position(current_node, new_node);
				current_node_token = (t_token *)current_node->content;
				if (tokens[index].kind == TK_CMD)
					bst_link_left_child(current_node, new_node);
				else if (cmp_kind(*current_node_token, tokens[index]) > 0)
				{
					bst_link_left_child(new_node, current_node->right_child);
					bst_link_right_child(current_node, new_node);
				}
				else
					bst_insert_node_left(current_node, new_node);
			}
		}
		current_node = new_node;
		++index;
	}
	return (bst_get_root(current_node));
}


t_btree_node	*parser(const char *str)
{
	t_token			*tokens;
	t_btree_node	*ast_root;

	tokens = lexer(str);
	ast_root = create_token_ast_from_tokens(tokens);
	return (ast_root);
}

const char	*token_str(t_token_kind kind)
{
	switch ((int)kind)
	{
		case TK_WORD:
			return ("WORD");
		case TK_WORD_DOUBLE_QUOTE:
			return ("DQ_WORD");
		case TK_CMD:
			return ("CMD");
		case TK_LESS:
			return ("<");
		case TK_GREATER:
			return (">");
		case TK_DOUBLE_LESS:
			return ("<<");
		case TK_DOUBLE_GREATER:
			return (">>");
		case TK_PIPE:
			return ("PIPE");
		case TK_ARR_END:
			return ("END");
		default :
			return ("ERR");

	}
}

int	x = 0;

void	print_tree(t_btree_node *root, int parent_num, char *s)
{
	if (root == NULL)
		return ;
	t_token	*token = root->content;
	int	index = x++;
	printf("index : %d, string : %s, kind : %s parent %d %s\n", index, token->str, token_str(token->kind), parent_num, s);
	print_tree(root->left_child, index, "L");
	print_tree(root->right_child, index, "R");
}

int main(void)
{
	t_btree_node	*ast;
	t_token			*tokens;
	//const char		*tc = "< infile1 cmd1 arg1 | cmd2 > outfile";
	const char		*test_code = "< infile1 << \"EOF ABC\" cmd1 cmd1_arg < file1 | <infile2 cmd2 cmd2_arg1 cmd2_arg2 <infile3 >> file2 | cmd3 cmd3_arg>> file3 > filetest3 | cmd4 \"cmd4_arg1 32413 43\"";
	size_t			index = 0;

	printf("==== LEXER TEST ====\n");
	tokens = lexer(test_code);
	while (tokens[index].kind != TK_ARR_END)
	{
		printf("index : %ld string : %s, kind :%d\n", index, tokens[index].str, tokens[index].kind);
		index++;
	}
	printf("==== LEXER TEST DONE ====\n");
	printf("==== AST CREATE ====\n");
	ast = create_token_ast_from_tokens(tokens);
	printf("==== AST DONE ====\n");
	printf("==== AST PRINT ====\n");
	print_tree(ast, -1, "ROOT");
}
