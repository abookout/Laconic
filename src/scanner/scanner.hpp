#ifndef LAC_SCANNER_HPP
#define LAC_SCANNER_HPP

#include "token.hpp"
#include <string>
#include <vector>

namespace LAC {
namespace Scanner {

class Scanner {
public:
  // default 'tors
  Scanner() = delete;
  explicit Scanner(std::string input);
  // ~Scanner();

  std::vector<Token> scan();

private:
  void scan_token();
  char advance_char();

  std::string input_str_;
  std::vector<Token> tokens_;

  // Points to first char in lexeme being scanned in input string
  int tok_start_;
  int tok_cur_;
  int tok_line_;
};
} // namespace Scanner
} // namespace LAC

#endif