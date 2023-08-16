#ifndef LAC_SCANNER_HPP
#define LAC_SCANNER_HPP

#include "token.hpp"
#include <string>
#include <vector>

namespace LAC {
namespace Scanner {

class Scanner {
public:
  Scanner();
  ~Scanner();

  void scan(std::string input);

  void get_tokens(std::vector<Token> tokens);
};
} // namespace Scanner
} // namespace LAC

#endif