include_guard()

include (monmgr/targetname_component)
include (monmgr/target)

function (monmgr_add _type _name)
  monmgr_targetname_component (${_name} NAME _target_name)
  monmgr_targetname_component (${_name} INTERNAL_NAMESPACE _internal_namespace)
  set (_internal_name "${_internal_namespace}-${_target_name}")

  # create the target
  cmake_language (CALL
    "add_${_type}" "${_internal_name}"
    ${ARGN}
  )
  cmake_language (CALL
    "add_${_type}"
    "${_name}" ALIAS "${_internal_name}"
  )
  monmgr_target (set_properties "${_name}"
    PROPERTIES
      EXPORT_NAME "${_target_name}"
      OUTPUT_NAME "${_target_name}"
  )

  # add shared library versioning properties
  monmgr_target (get_property "${_name}"
    _lib_type
    TYPE
  )
  if (_lib_type STREQUAL "SHARED_LIBRARY")
    monmgr_target (set_properties "${_name}"
      PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION}
    )
  endif()

  # make target installation relocatable
  if (${_project_entry}_INSTALL_RELOCATABLE)
    set (_rpath "\$ORIGIN")
    if (_type STREQUAL "executable")
      string (APPEND _rpath "/../${CMAKE_INSTALL_LIBDIR}")
    endif()
    monmgr_target (set_properties "${_name}"
      PROPERTIES
        INSTALL_RPATH "${_rpath}"
    )
    if (_lib_type STREQUAL "STATIC_LIBRARY")
      monmgr_target (set_properties "${_name}"
        PROPERTIES
          POSITION_INDEPENDENT_CODE ON
      )
    endif()
  endif()
endfunction()
