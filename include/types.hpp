#ifndef LAC_TYPES_HPP
#define LAC_TYPES_HPP

namespace LAC {

enum TokenType {
  // Arithmetic
  PLUS = '+',
  MINUS = '-',
  TIMES = '*',
  DIVIDE = '/',

  // Logic and precedence
  AND = '&',
  OR = '?',
  XOR = '^',
  LESS = '<',
  GREATER = '>',

  LEFT_PAREN = '(',
  RIGHT_PAREN = ')',

  // Blocks
  CUR_BLOCK = '!',
  RET_VALUE = '%',
  BLOCK_PARAMS = '_',
  LEFT_BRACKET = '[',
  RIGHT_BRACKET = ']',
  NECK = '|',
  LENGTH = '#',
  ACCESSOR = '@',
  ASSIGNMENT = ':',
  CONTINUE = '{',
  BREAK = '}',

  // Symbols for defining lac literals
  PERIOD = '.',
  STATEMENT_LIT = '$',
  CHAR_LIT = '\'',
  STR_LIT = '\"',

  TYPEOF = '\\',
  SEMICOLON = ';',
  COMMA = ',',

  // Literals
  IDENTIFIER = 1000, // ascii chars out of numeric order, ensures no overlap

  // Special
  EOF
};
}

#endif