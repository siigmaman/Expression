add_library(EXPRESSION STATIC EXPRESSION.cpp EXPRESSION.h NODE.h)

target_include_directories(EXPRESSION PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(differentiator differentiator.cpp)
target_link_libraries(differentiator PRIVATE EXPRESSION)