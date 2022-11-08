cmake_minimum_required (VERSION 3.24)

project (monmgr
  VERSION 0.2
)

###################################################################################################
# Project CMake Module Path
###################################################################################################

list (APPEND
  CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/cmake"
)

###################################################################################################
# Project Includes
###################################################################################################

include (CMakePackageConfigHelpers)
include (CTest)
include (GNUInstallDirs)

include (monmgr/add)
include (monmgr/target)
include (monmgr/install_component)

###################################################################################################
# Project Meta Information
###################################################################################################

string (TOUPPER
  "${PROJECT_NAME}"
  _project_entry
)
string (MAKE_C_IDENTIFIER
  "${_project_entry}"
  _project_entry
)

###################################################################################################
# Project Generic Options
###################################################################################################

# select if libraries with an unspecified build type are built as SHARED or STATIC
option (BUILD_SHARED_LIBS
  "Flag to cause 'add_library()' to create SHARED libraries (default: ON)"
  ON
)

# set default build type and define a multiple choice drop down list for gui support
set (_build_types
  "Release"
  "Debug"
  "RelWithDebInfo"
  "MinSizeRel"
)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set (CMAKE_BUILD_TYPE
    "Release"
    CACHE STRING
    "Specifies the build type on single-configuration generators"
    FORCE
  )
  set_property (CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
      ${_build_types}
  )
endif()
unset (_built_types)

# allow to disable the project's tests
if (NOT DEFINED ${_project_entry}_BUILD_TESTING)
  set (_build_testing OFF)
  if (BUILD_TESTING)
    set (_build_testing ${BUILD_TESTING})
  endif()
  option (${_project_entry}_BUILD_TESTING
    "Build ${PROJECT_NAME} tests"
    ${_build_testing}
  )
  unset (_build_testing)
endif()

# allow to customize the install location of the project config and version file
set (${_project_entry}_CONFIG_INSTALL_DIR
  "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  CACHE PATH
  "${PROJECT_NAME} package configuration and CMake scripts installation path prefix. \
  (default: ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})"
)
mark_as_advanced (${_project_entry}_CONFIG_INSTALL_DIR)

# allow to customize the project's target namespace
set (${_project_entry}_TARGET_NAMESPACE
  "${PROJECT_NAME}"
  CACHE STRING
  "${PROJECT_NAME} target namespace"
)
mark_as_advanced (${_project_entry}_TARGET_NAMESPACE)
set (_ns "${${_project_entry}_TARGET_NAMESPACE}")

# allow to customize the project's c++ standard
set (${_project_entry}_CXX_STANDARD
  17
  CACHE STRING
  "${PROJECT_NAME} C++ standard"
)
mark_as_advanced (${_project_entry}_CXX_STANDARD)

# make the project installation relocatable
option (${_project_entry}_INSTALL_RELOCATABLE
  "Install ${PROJECT_NAME} to be relocatable"
  ON
)
mark_as_advanced (${_project_entry}_INSTALL_RELOCATABLE)

###################################################################################################
# Project Subdirectories
###################################################################################################

add_subdirectory (3rdparty)
add_subdirectory (src)

###################################################################################################
# Project CMake Package Config Script
###################################################################################################

configure_package_config_file (
  ${PROJECT_NAME}-config.cmake.in
  ${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION
    ${${_project_entry}_CONFIG_INSTALL_DIR}
)

write_basic_package_version_file (
  ${PROJECT_NAME}-config-version.cmake
  COMPATIBILITY SameMajorVersion
)

install (
  FILES
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION
    ${${_project_entry}_CONFIG_INSTALL_DIR}
  COMPONENT ${PROJECT_NAME}-devel
)
