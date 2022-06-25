add_library(Instructions INTERFACE ./inst.h)
add_library(Traps INTERFACE ./traps.h)
add_library(Core ./core.cc ./core.h)
add_library(Utils ./utils.cc ./utils.h)
add_library(Stack ./stack.cc ./stack.h)
target_link_libraries(Stack PUBLIC Core)

add_library(Vm ./vm.h ./vm.cc)
target_link_libraries(Vm PRIVATE Stack Core)
