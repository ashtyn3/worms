
project('worms', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

# incdir = include_directories('./src')
subdir('./src')
executable('worms',
           './src/main.cc',
           install : true, link_with: [vm,traps, core, inst, module],link_args: ['-static'])

executable('worms_wr',
           './src/wr/wr.cc',
           install : true, link_with: [lexer, parser], link_args: ['-static', '-g'] )
