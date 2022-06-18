nanoid = library('Nanoid', './snailer_nanoid.h',)
module = library('Module', './module.h','./module.cc', link_with: [nanoid])
byte = static_library('Byte','./byte_gen.h', './byte_gen.cc', link_with: [module])

