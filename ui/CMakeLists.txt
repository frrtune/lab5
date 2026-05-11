add_executable(lab5_ui
    ui.cpp
    main.cpp
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

find_library(PDCURSES_LIB NAMES pdcurses libpdcurses PATHS "C:/msys64/mingw64/lib")
find_path(PDCURSES_INCLUDE NAMES curses.h pdcurses.h PATHS "C:/msys64/mingw64/include" "C:/msys64/mingw64/include/pdcurses")

target_link_libraries(lab5_ui
    ${PDCURSES_LIB}
    array_sequence
    exceptions
    sequence
    dynamic_array
)
target_include_directories(lab5_ui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${PDCURSES_INCLUDE}
)