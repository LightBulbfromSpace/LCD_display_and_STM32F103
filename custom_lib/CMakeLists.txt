cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

include_directories(headers)
include_directories(headers/examples)

add_library(custom STATIC "src/utils.c" "src/spi.c" "src/display.c" "src/examples/running_line.c" "src/examples/ball.c")

set_target_properties(custom PROPERTIES PUBLIC_HEADER
"headers/*.h")
