###################################################################################################
# Project Private Targets
###################################################################################################

###################################################################################################
# Project Target Dependencies
###################################################################################################

monmgr_target (link_libraries ${_ns}::monster-menagerie
  PRIVATE
    ${_ns}::config
    ${_ns}::menagerie
    fmt::fmt-header-only
)

monmgr_target (link_libraries ${_ns}::menagerie
  PUBLIC
    ${_ns}::config
  PRIVATE
    $<BUILD_INTERFACE:fmt::fmt-header-only>
)

###################################################################################################
# Project Target Sources
###################################################################################################

monmgr_target (sources ${_ns}::monster-menagerie
  PRIVATE
    main.cpp
)

monmgr_target (sources ${_ns}::menagerie
  PRIVATE
    Menagerie.cpp
    LonelyMonster.cpp
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS "${PROJECT_SOURCE_DIR}/src"
      FILES
        LonelyMonster.hpp
  PUBLIC
    FILE_SET public_headers
      TYPE HEADERS
      BASE_DIRS "${PROJECT_SOURCE_DIR}/src"
      FILES
        Menagerie.hpp
        MonsterBase.hpp
)
