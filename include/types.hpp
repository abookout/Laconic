#ifndef LAC_TYPES_HPP
#define LAC_TYPES_HPP

namespace LAC {

enum TokenType {
  // Arithmetic
  TOK_PLUS = '+',
  TOK_MINUS = '-',
  TOK_TIMES = '*',
  TOK_DIVIDE = '/',

  // Logic and precedence
  TOK_AND = '&',
  TOK_OR = '?',
  TOK_XOR = '^',
  TOK_LESS = '<',
  TOK_GREATER = '>',

  TOK_LEFT_PAREN = '(',
  TOK_RIGHT_PAREN = ')',

  // Blocks
  TOK_CUR_BLOCK = '!',
  TOK_RET_VALUE = '%',
  TOK_BLOCK_PARAMS = '_',
  TOK_LEFT_BRACKET = '[',
  TOK_RIGHT_BRACKET = ']',
  TOK_NECK = '|',
  TOK_LENGTH = '#',
  TOK_ACCESSOR = '@',
  TOK_ASSIGNMENT = ':',
  TOK_CONTINUE = '{',
  TOK_BREAK = '}',

  // Symbols for defining lac literals
  TOK_PERIOD = '.',
  TOK_STATEMENT_LIT = '$',
  TOK_CHAR_LIT = '\'',
  TOK_STR_LIT = '\"',

  TOK_TYPEOF = '\\',
  TOK_SEMICOLON = ';',
  TOK_COMMA = ',',

  // Literals
  TOK_IDENTIFIER = 1000, // ascii chars out of numeric order, ensures no overlap

  // Special
  TOK_EOF
};
}

#endif