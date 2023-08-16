#ifndef LAC_TOKEN_HPP
#define LAC_TOKEN_HPP

#include "../types.hpp"
#include <memory>
#include <string>

namespace LAC {

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
} // namespace LAC

#endif