cmake_minimum_required (VERSION 3.5)

project(worms CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

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
