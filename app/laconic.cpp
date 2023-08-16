#include "errors.hpp"
#include "scanner.hpp"
#include <iostream>
#include <sstream>
#include <string>

using Scanner = LAC::Scanner::Scanner;
using ErrorReporter = LAC::ErrorReporter;

void run(std::string code, ErrorReporter &err_reporter) {
  Scanner scanner(code, err_reporter);
  // TODO: get tokens
  // TODO: execute
}

void run_repl(ErrorReporter &err_reporter) {
  std::string buf;
  while (1) {
    std::cout << "> ";
    std::getline(std::cin, buf);
    run(buf, err_reporter);
  }
}

int main(int argc, char *argv[]) {
  ErrorReporter err_reporter;
  if (argc == 1) {
    run_repl(err_reporter);
    return 0;
  }

  return 1;
}