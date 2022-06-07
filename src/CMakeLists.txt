add_subdirectory(lib)
add_subdirectory(wr)

add_executable(worms main.cc)

target_link_libraries(worms PUBLIC VM)
target_link_libraries(worms PUBLIC Instructions)
target_link_libraries(worms PUBLIC Core)
target_link_libraries(worms PUBLIC Traps)
target_link_libraries(worms PUBLIC Stack)
