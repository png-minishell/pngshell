/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:39:29 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 18:02:28 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "parser.h"

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

char **envp;
char **set;

int main(int argc, char **argv, char **env)
{
	t_btree_node	*ast;
	t_token			*tokens;
	const char		*tc2 = "cat -e << Makefile | cat -e  | cat -e > outfile";
	//const char		*tc2 = "< infile1 cmd1 arg1 | cmd2 > outfile | cmd3 | < infile2 > outfile2";
	const char		*test_code = "< infile1 << \"EOF ABC\" cmd1 cmd1_arg < file1 | <infile2 cmd2 cmd2_arg1 cmd2_arg2 <infile3 >> file2 | cmd3 cmd3_arg>> file3 > filetest3 | cmd4 \"cmd4_arg1 32413 43\"";
	size_t			index = 0;

	envp = env;
	set = env;
	if (argc == 1)
		printf("%s", argv[0]);
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
	x = 0;
	ast = parser(tc2);
	print_tree(ast, -1, "ROOT");
}
