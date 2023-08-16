#ifndef LAC_ERRORS_HPP
#define LAC_ERRORS_HPP

#include <iostream>
#include <string>

namespace LAC {

namespace Exception {
class InternalException : public std::runtime_error {
  //   std::string message;

public:
  //   inline virtual const char *what() const noexcept { return
  //   message.c_str(); }

  explicit InternalException(const std::string &msg)
      : std::runtime_error(msg) {}
};
} // namespace Exception

// enum LogLevel { FATAL, ERROR, WARN, DEBUG, INFO, TRACE };

class ErrorReporter {
public:
  ErrorReporter();
  // ErrorReporter() = delete;
  // explicit ErrorReporter(LogLevel log_level);
  void report(int line, std::string where, std::string msg);
  void report(int line, std::string msg);

  /**
   * Check if there has been an error since last clearing the error flag
   */
  bool had_error();

  /**
   * Clear the error flag
   */
  void clear_error();

private:
  // LogLevel log_level_;
  bool had_error_;
};

} // namespace LAC

#endif