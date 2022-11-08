###################################################################################################
# Project Config Target
###################################################################################################

add_library (${_ns}-config INTERFACE)
set_target_properties (${_ns}-config
  PROPERTIES
    EXPORT_NAME config
    OUTPUT_NAME config
)
add_library (${_ns}::config ALIAS ${_ns}-config)

target_compile_features (${_ns}-config
  INTERFACE
    cxx_std_${${_project_entry}_CXX_STANDARD}
)

###################################################################################################
# Project Public Dependencies
###################################################################################################

find_package (fmt REQUIRED)

###################################################################################################
# Project Public Targets
###################################################################################################

add_executable (${_ns}-monster-menagerie)
set_target_properties (${_ns}-monster-menagerie
  PROPERTIES
    EXPORT_NAME monster-menagerie
    OUTPUT_NAME monster-menagerie
)
add_executable (${_ns}::monster-menagerie ALIAS ${_ns}-monster-menagerie)

if (${_project_entry}_INSTALL_RELOCATABLE)
  set_target_properties (${_ns}-monster-menagerie
    PROPERTIES
      INSTALL_RPATH \$ORIGIN/../${CMAKE_INSTALL_LIBDIR}
  )
endif()

add_library (${_ns}-menagerie)
set_target_properties (${_ns}-menagerie
  PROPERTIES
    EXPORT_NAME menagerie
    OUTPUT_NAME menagerie
)
add_library (${_ns}::menagerie ALIAS ${_ns}-menagerie)

if (${_project_entry}_INSTALL_RELOCATABLE)
  set_target_properties (${_ns}-menagerie
    PROPERTIES
      INSTALL_RPATH \$ORIGIN
  )
endif()

if (BUILD_SHARED_LIBS)
  set_target_properties (${_ns}-menagerie
    PROPERTIES
      SOVERSION ${PROJECT_VERSION_MAJOR}
      VERSION ${PROJECT_VERSION}
  )
endif()

###################################################################################################
# Project Source
###################################################################################################

add_subdirectory (${_ns})

###################################################################################################
# Project Install Public Targets
###################################################################################################

install (
  TARGETS
    ${_ns}-config
    ${_ns}-monster-menagerie
    ${_ns}-menagerie
  EXPORT
    ${_ns}-targets
  RUNTIME
    COMPONENT ${PROJECT_NAME}-runtime
  LIBRARY
    COMPONENT ${PROJECT_NAME}-runtime
    NAMELINK_COMPONENT ${PROJECT_NAME}-devel
  ARCHIVE
    COMPONENT ${PROJECT_NAME}-devel
  FILE_SET public_headers
    COMPONENT ${PROJECT_NAME}-devel
)

install (
  EXPORT
    ${_ns}-targets
  DESTINATION
    ${${_project_entry}_CONFIG_INSTALL_DIR}
  NAMESPACE
    ${_ns}::
  COMPONENT ${PROJECT_NAME}-devel
)
