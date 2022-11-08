###################################################################################################
# Project Private Targets
###################################################################################################

###################################################################################################
# Project Target Dependencies
###################################################################################################

target_link_libraries (${_ns}-monster-menagerie
  PRIVATE
    ${_ns}-config
    ${_ns}-menagerie
    fmt::fmt-header-only
)

target_link_libraries (${_ns}-menagerie
  PUBLIC
    ${_ns}-config
  PRIVATE
    $<BUILD_INTERFACE:fmt::fmt-header-only>
)

###################################################################################################
# Project Target Sources
###################################################################################################

target_sources (${_ns}-monster-menagerie
  PRIVATE
    main.cpp
)

target_sources (${_ns}-menagerie
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
