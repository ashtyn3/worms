nanoid = library('Nanoid', './snailer_nanoid.h',)

module = library('Module', './module.h','./module.cc', link_with: [nanoid])

byte = library('Byte','./byte_gen.h', './byte_load.h', './byte_gen.cc', './byte_load.cc', link_with: [module])

