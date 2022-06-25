cmake_minimum_required (VERSION 3.5)

project(worms CXX)
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(./external/spdlog)
add_subdirectory(./src/snailer)
add_subdirectory(./src/include)
add_subdirectory(./src/lib)


add_executable(worms-c ./src/main.cc)
# target_include_directories(worms-c PRIVATE ./external/spdlog)
target_link_libraries(worms-c PRIVATE Vm ArgParse Byte spdlog)


add_subdirectory(./src/wr/compiler/)
add_executable(worms-wr ./src/wr/wr.cc)
target_link_libraries(worms-wr PRIVATE Parser Lexer spdlog Generator)
