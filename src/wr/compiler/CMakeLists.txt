add_library(Lexer ./lex.cc ./lex.h)
target_link_libraries(Lexer PRIVATE spdlog)

add_library(Parser ./parse.cc ./parse.h ./parser.h)
target_link_libraries(Parser PRIVATE spdlog)

add_library(Generator ./gen.cc ./gen.h)
target_link_libraries(Generator PRIVATE spdlog ArgParse Byte Core)
