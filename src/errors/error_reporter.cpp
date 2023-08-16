#include <iostream>
#include <string>

#include "errors.hpp"
#include "fmt/core.h"

namespace LAC {

ErrorReporter::ErrorReporter() : had_error_(false) {}

void ErrorReporter::report(int line, std::string where, std::string msg) {
  had_error_ = true;
  std::cout << fmt::format("Error (line {}) {}: {}\n", line, where, msg);

  if (!std::cout) {
    // Error printing failed, panic
    throw LAC::Exception::InternalException("Could not write to stdout\n");
  }
}

void ErrorReporter::report(int line, std::string msg) { report(line, "", msg); }

bool ErrorReporter::had_error() { return had_error_; }

void ErrorReporter::clear_error() { had_error_ = false; }
} // namespace LAC