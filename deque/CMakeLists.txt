add_library(deque INTERFACE)
target_include_directories(deque INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(deque INTERFACE sequence array_sequence)