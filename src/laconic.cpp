#include <iostream>
#include <sstream>
#include <string>

void run(std::string code) {}

void run_repl() {
  std::string buf;
  while (1) {
    std::getline(std::cin, buf);
    run(buf);
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // REPL
    run_repl();
    return 0;
  }
}