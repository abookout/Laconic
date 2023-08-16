cmake_minimum_required(VERSION 3.20)
project(laconic LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

include_directories(include)
link_directories(src)

file(GLOB ERRORS_SOURCES "${CMAKE_SOURCE_DIR}/src/errors/*.cpp")
file(GLOB SCANNER_SOURCES "${CMAKE_SOURCE_DIR}/src/scanner/*.cpp")

add_library(errors STATIC ${ERRORS_SOURCES})
add_library(scanner STATIC ${SCANNER_SOURCES})

# Include the fmt library from the vendor directory in the laconic executable
add_subdirectory(vendor/fmt)
include_directories(vendor/fmt/include)

add_executable(laconic app/laconic.cpp)
target_link_libraries(laconic PUBLIC errors scanner fmt::fmt)