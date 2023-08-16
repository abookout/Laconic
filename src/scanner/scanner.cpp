#include "scanner.hpp"
#include "fmt/core.h"

namespace LAC {
namespace Scanner {

Scanner::Scanner(std::string input, ErrorReporter &err_reporter)
    : input_str_(input), err_reporter_(err_reporter), tok_start_(0),
      tok_cur_(0), tok_line_(1) {}

char Scanner::advance_char() {
  char cur_char = input_str_[tok_cur_];
  ++tok_cur_;
  return cur_char;
}

void Scanner::scan_token() {
  // implementation inspired by
  // http://craftinginterpreters.com/scanning.html#recognizing-lexemes
  char c = advance_char();

  // TODO: make tokens
  switch (c) {
    // Arithmetic
  case TOK_PLUS:
    break;
  case TOK_MINUS:
    break;
  case TOK_TIMES:
    break;
  case TOK_DIVIDE:
    break;

  // Logic and precedence
  case TOK_AND:
    break;
  case TOK_OR:
    break;
  case TOK_XOR:
    break;
  case TOK_LESS:
    break;
  case TOK_GREATER:
    break;

  case TOK_LEFT_PAREN:
    break;
  case TOK_RIGHT_PAREN:
    break;

  // Blocks
  case TOK_CUR_BLOCK:
    break;
  case TOK_RET_VALUE:
    break;
  case TOK_BLOCK_PARAMS:
    break;
  case TOK_LEFT_BRACKET:
    break;
  case TOK_RIGHT_BRACKET:
    break;
  case TOK_NECK:
    break;
  case TOK_LENGTH:
    break;
  case TOK_ACCESSOR:
    break;
  case TOK_ASSIGNMENT:
    break;
  case TOK_CONTINUE:
    break;
  case TOK_BREAK:
    break;

  // Symbols for defining lac literals
  case TOK_PERIOD:
    break;
  case TOK_STATEMENT_LIT:
    break;
  case TOK_CHAR_LIT:
    break;
  case TOK_STR_LIT:
    break;

  case TOK_TYPEOF:
    break;
  case TOK_SEMICOLON:
    break;
  case TOK_COMMA:
    break;
  default:
    err_reporter_.report(tok_line_, "",
                         fmt::format("Unrecognized token {}", (char)c));
    break;
  }
}

std::vector<Token> Scanner::scan() {
  while (tok_cur_ < input_str_.length()) {
    // Scan each token
    tok_start_ = tok_cur_;
    scan_token();
  }

  // Reached EOF
  tokens_.push_back(Token(TOK_EOF, "", std::make_shared<int>(0), tok_line_));

  return tokens_;
}

} // namespace Scanner
} // namespace LAC