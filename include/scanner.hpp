#ifndef LAC_SCANNER_HPP
#define LAC_SCANNER_HPP

#include "errors.hpp"
#include "fmt/core.h"
#include "types.hpp"
#include <memory>
#include <string>
#include <vector>

using ErrorReporter = LAC::ErrorReporter;

namespace LAC {
namespace Scanner {

/**
 * Stores the intermediate representation of tokens parsed by the scanner.
 */
class Token {
public:
  Token() = delete;
  explicit inline Token(TokenType t, std::string lex, std::shared_ptr<void> lit,
                        int line)
      : type(t), lexeme(lex), literal(std::move(lit)), from_line(line) {}

  inline std::string to_string() const {
    // get value of literal
    std::string lit_str;
    if (this->literal == nullptr) {
      lit_str = "null";
    } else {
      switch (type) {
      case TokenType::TOK_DOUBLE:
        lit_str = std::to_string(*static_cast<double *>(this->literal.get()));
        break;
      case TokenType::TOK_INT:
        lit_str = std::to_string(*static_cast<int *>(this->literal.get()));
        break;
      case TokenType::TOK_IDENTIFIER:
        lit_str = *static_cast<std::string *>(this->literal.get());
        break;
      default:
        std::cerr << "Type " << (char)type
                  << " not supported for token to_string\n";
      }
    }

    return fmt::format("({} {} {})", (char)type, lexeme, lit_str);
  }

  const TokenType type;
  const std::string lexeme;
  // shared_ptr<void> stores any data while still calling the correct dtor
  const std::shared_ptr<void> literal;
  const int from_line;
};

class Scanner {
public:
  // default 'tors
  Scanner() = delete;
  explicit Scanner(std::string input, ErrorReporter &err_reporter);
  // ~Scanner();

  std::vector<Token> scan();

private:
  bool at_eof();
  void scan_token();
  // Returns the current char and advances tok_cur_
  char advance_char();
  char peek_char();
  char peek_next();
  std::string get_token_substring();

  // Returns true and advances tok_cur_ if the current char matches c, false
  // otherwise. For multi-char tokens
  // bool advance_if_matched(char c);
  void add_token(TokenType type);
  void add_token(TokenType type, std::shared_ptr<void> literal);

  // if decimal_prefixed, the number literal had a decimal point before any
  // digits
  void scan_number(bool decimal_prefixed = false);
  void scan_identifier();

  static bool is_digit(char c);
  static bool is_alpha(char c);
  static bool is_alnum(char c);

  std::string input_str_;
  ErrorReporter &err_reporter_;
  std::vector<Token> tokens_;

  // Points to first char in lexeme being scanned in input string
  size_t tok_start_;
  size_t tok_cur_;
  size_t tok_line_;
};
} // namespace Scanner
} // namespace LAC

#endif