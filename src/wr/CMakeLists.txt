add_subdirectory(compiler)

add_executable(worms_wr wr.cc)

target_link_libraries(worms_wr PUBLIC Lexer)
target_link_libraries(worms_wr PUBLIC Parser)
