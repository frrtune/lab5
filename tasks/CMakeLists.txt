add_library(dictionary dictionary.cpp)
target_include_directories(dictionary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dictionary PUBLIC deque array_sequence)