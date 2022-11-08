include (FetchContent)

option (
  BOOTSTRAP_LIBFMT
  "BOOTSTRAP Libfmt"
  ON
)

if (BOOTSTRAP_LIBFMT)
  FetchContent_Declare (
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
    GIT_SHALLOW TRUE
    OVERRIDE_FIND_PACKAGE
  )
endif()
