# set compiler
set (CMAKE_C_COMPILER
  gcc
)
set (CMAKE_CXX_COMPILER
  g++
)

# ccache setup
find_program (CCACHE_EXECUTABLE
  NAMES
    ccache
    ccache-swig
)

if (CCACHE_EXECUTABLE)
  set (CMAKE_C_COMPILER_LAUNCHER
    ${CCACHE_EXECUTABLE}
  )
  set (CMAKE_CXX_COMPILER_LAUNCHER
    ${CCACHE_EXECUTABLE}
  )
endif()

# compiler flags
set (CMAKE_C_FLAGS_INIT
  -Werror
)
set (CMAKE_CXX_FLAGS_INIT
  -Werror
)
