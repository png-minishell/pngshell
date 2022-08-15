
#ifndef LEXER_H
#define LEXER_H

typedef enum	e_token_kind
{
	TK_EOF = '\0',
	TK_DOLLAR = '$',
	TK_PAREN_LEFT = '(',
	TK_PAREN_RIGHT = ')',
	TK_LESS = '<',
	TK_GREATER = '>',
	TK_OR = '|',
	TK_AND = '&',
	TK_SINGLE_QUOTE = '\'',
	TK_DOUBLE_QUOTE = '\"',
	TK_ESCAPE = '\\',
	TK_ASTERISK = '*',
	TK_WORD,
	TK_LESS_LESS,
	TK_GREATER_GREATER,
	TK_OR_OR,
	TK_AND_AND,
	TK_ERROR = -1,
}	t_token_kind;

#endif
