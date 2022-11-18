cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

include_directories(headers)

add_library(custom STATIC "src/utils.c" "src/spi.c" "src/display.c" "src/examples.c")

set_target_properties(custom PROPERTIES PUBLIC_HEADER
"headers/*.h")
