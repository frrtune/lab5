cmake_minimum_required(VERSION 3.23)
project(lab5 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)


find_library(PDCURSES_LIB NAMES pdcurses libpdcurses PATHS "C:/msys64/mingw64/lib")
find_path(PDCURSES_INCLUDE NAMES curses.h pdcurses.h PATHS "C:/msys64/mingw64/include" "C:/msys64/mingw64/include/pdcurses")

add_subdirectory(googletest-1.17.0)
add_subdirectory(exceptions)
add_subdirectory(sequence)
add_subdirectory(dynamic_array)
add_subdirectory(linked_list)
add_subdirectory(array_sequence)
add_subdirectory(list_sequence)
add_subdirectory(bit_sequence)

add_subdirectory(tests)
add_subdirectory(ui)