#include "scanner/scanner.hpp"
#include <iostream>
#include <sstream>
#include <string>

using Scanner = LAC::Scanner::Scanner;

void run(std::string code) {
  Scanner scanner(code);
  // TODO: get tokens
  // TODO: execute
}

void run_repl() {
  std::string buf;
  while (1) {
    std::cout << "> ";
    std::getline(std::cin, buf);
    run(buf);
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    run_repl();
    return 0;
  }

  return 1;
}