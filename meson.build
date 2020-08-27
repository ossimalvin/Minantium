project( 'minantium', 'c' )
cc = meson.get_compiler( 'c' )

# Depends
libmdep = cc.find_library( 'm', required : false )
libdldep = cc.find_library( 'dl' )

curldep = dependency( 'libcurl' )
glfwdep = dependency( 'glfw3' )
gludep = dependency( 'glu' )
threaddep = dependency( 'threads' )

# Includes
inc_dirs = include_directories( 'deps/glew/include','deps/glfw/include','deps/lodepng','deps/noise','deps/sqlite','deps/tinycthread' )
int_source_files = [ 'src/auth.c','src/client.c','src/cube.c','src/db.c','src/item.c','src/main.c','src/map.c','src/matrix.c','src/ring.c','src/sign.c','src/util.c','src/world.c' ]
ext_source_files = [ 'deps/glew/src/glew.c','deps/lodepng/lodepng.c','deps/noise/noise.c','deps/sqlite/sqlite3.c','deps/tinycthread/tinycthread.c' ]

# Executable
executable('minantium', int_source_files, ext_source_files, include_directories : inc_dirs, dependencies: [ libmdep, libdldep, curldep, glfwdep, gludep, threaddep ] )
