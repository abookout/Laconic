#include "scanner.hpp"
#include "fmt/core.h"

namespace LAC {
namespace Scanner {

Scanner::Scanner(std::string input, ErrorReporter &err_reporter)
    : input_str_(input), err_reporter_(err_reporter), tokens_{}, tok_start_(0),
      tok_cur_(0), tok_line_(1) {}

bool Scanner::at_eof() { return tok_cur_ >= input_str_.length(); }

char Scanner::advance_char() {
  char cur_char = input_str_[tok_cur_];
  ++tok_cur_;
  return cur_char;
}

char Scanner::peek_char() {
  if (at_eof()) {
    return '\0';
  }
  return input_str_[tok_cur_];
}

char Scanner::peek_next() {
  if (tok_cur_ + 1 >= input_str_.length()) {
    return '\0';
  }
  return input_str_[tok_cur_ + 1];
}

bool Scanner::is_digit(char c) { return c >= '0' && c <= '9'; }
bool Scanner::is_alpha(char c) {
  // TODO: not allowing underscores for now because of reserved operator making
  // it hard to parse
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool Scanner::is_alnum(char c) { return is_digit(c) || is_alpha(c); }

std::string Scanner::get_token_substring() {
  return input_str_.substr(tok_start_, tok_cur_ - tok_start_);
}

// bool Scanner::advance_if_matched(char c) {
//   if (at_eof() || input_str_[tok_cur_] != c) {
//     return false;
//   }
//   ++tok_cur_;
//   return true;
// }

void Scanner::add_token(TokenType type) { add_token(type, nullptr); }

void Scanner::add_token(TokenType type, std::shared_ptr<void> literal) {
  tokens_.emplace_back(type, get_token_substring(), std::move(literal),
                       tok_line_);
}

void Scanner::scan_number(bool decimal_prefixed) {
  // Consume whole number (pre-decimal)
  while (is_digit(peek_char())) {
    advance_char();
  }

  // Optional decimal makes number a float
  bool is_float = decimal_prefixed;
  if (peek_char() == '.' /*&& is_digit(peek_next())*/) {
    if (decimal_prefixed) {
      err_reporter_.report(tok_line_, "Invalid number literal");
      return;
    }

    is_float = true;
    advance_char(); // consume decimal

    // Consume rest of number (post-decimal)
    while (is_digit(peek_char())) {
      advance_char();
    }
  }

  try {
    if (is_float) {
      add_token(TOK_DOUBLE,
                std::make_shared<double>(std::stod(get_token_substring())));
    } else {
      add_token(TOK_INT,
                std::make_shared<int>(std::stoi(get_token_substring())));
    }
  } catch (std::invalid_argument &e) {
    err_reporter_.report(tok_line_, fmt::format("Invalid number literal",
                                                get_token_substring()));
  } catch (std::out_of_range &e) {
    err_reporter_.report(
        tok_line_,
        fmt::format(
            "Number literal out of range. If this is an integer, this will be "
            "handled after implementing arbitrary precision integers.",
            get_token_substring()));
  }
}

void Scanner::scan_identifier() {
  // Consume whole identifier
  while (is_alnum(peek_char())) {
    advance_char();
  }

  // No builtin keywords so all will be identifiers
  add_token(TOK_IDENTIFIER);
}

std::vector<Token> Scanner::scan() {
  while (!at_eof()) {
    // Scan each token
    scan_token();
  }

  // Reached EOF
  tokens_.emplace_back(TOK_EOF, "EOF", nullptr, tok_line_);

  return tokens_;
}

void Scanner::scan_token() {
  // implementation inspired by
  // http://craftinginterpreters.com/scanning.html#recognizing-lexemes

  // Reset start of token to current position
  tok_start_ = tok_cur_;

  char c = advance_char();

  // TODO: make tokens
  switch (c) {
    // Arithmetic
  case TOK_PLUS:
    add_token(TOK_PLUS);
    break;
  case TOK_MINUS:
    add_token(TOK_MINUS);
    break;
  case TOK_TIMES:
    add_token(TOK_TIMES);
    break;
  case TOK_DIVIDE:
    add_token(TOK_DIVIDE);
    break;

  // Logic and precedence
  case TOK_AND:
    add_token(TOK_AND);
    break;
  case TOK_OR:
    add_token(TOK_OR);
    break;
  case TOK_XOR:
    add_token(TOK_XOR);
    break;
  case TOK_EQUAL:
    add_token(TOK_EQUAL);
    break;
  case TOK_LESS:
    add_token(TOK_LESS);
    break;
  case TOK_GREATER:
    add_token(TOK_GREATER);
    break;

  case TOK_LEFT_PAREN:
    add_token(TOK_LEFT_PAREN);
    break;
  case TOK_RIGHT_PAREN:
    add_token(TOK_RIGHT_PAREN);
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

  // case TOK_PERIOD:
  //   break;
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

  case ' ':
  case '\t':
  case '\r':
    break; // ignore
  case '\n':
    ++tok_line_;
    break;

  default:
    if (is_digit(c) || c == TOK_PERIOD) {
      scan_number(c == TOK_PERIOD);
    } else if (is_alpha(c)) {
      scan_identifier();
    } else {
      // TODO: search trie for identifier before reporting error
      err_reporter_.report(tok_line_, "",
                           fmt::format("Unexpected character {}", (char)c));
    }
    break;
  }
}

} // namespace Scanner
} // namespace LAC