#ifndef LAC_SCANNER_HPP
#define LAC_SCANNER_HPP

#include "errors.hpp"
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
  void scan_token();
  char advance_char();

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