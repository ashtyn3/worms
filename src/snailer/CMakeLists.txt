add_library(Nanoid INTERFACE ./snailer_nanoid.h)

add_library(Module ./module.cc ./module.h)
target_link_libraries(Module PRIVATE spdlog)

add_library(Byte ./byte_load.h ./byte_gen.h ./byte_gen.cc  ./byte_load.cc )
target_link_libraries(Byte PRIVATE Module)
target_link_libraries(Byte PRIVATE spdlog)
