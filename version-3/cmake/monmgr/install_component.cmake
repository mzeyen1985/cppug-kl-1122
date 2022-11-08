include_guard()

include (monmgr/targetname_component)

function (monmgr_install_component _name)
  list (LENGTH ARGN _num_targets)
  if (_num_targets LESS 1)
    message (FATAL_ERROR
      "No targets were given! At least 1 target is required."
    )
  endif()

  foreach (_target IN LISTS ARGN)
    monmgr_targetname_component (${_target} NAME _target_name)
    monmgr_targetname_component (${_target} INTERNAL_NAMESPACE _internal_namespace)
    list (APPEND
      _internal_targets
      "${_internal_namespace}-${_target_name}"
    )
  endforeach()

  install (
    TARGETS ${_internal_targets}
    EXPORT ${_name}-targets
    RUNTIME
      COMPONENT ${PROJECT_NAME}-runtime
    LIBRARY
      COMPONENT ${PROJECT_NAME}-runtime
      NAMELINK_COMPONENT ${PROJECT_NAME}-devel
    ARCHIVE
      COMPONENT ${PROJECT_NAME}-devel
    FILE_SET public_headers
      COMPONENT ${PROJECT_NAME}-devel
    FILE_SET interface_headers
      COMPONENT ${PROJECT_NAME}-devel
  )

  install (
    EXPORT
      ${_name}-targets
    DESTINATION
      ${${_project_entry}_CONFIG_INSTALL_DIR}
    NAMESPACE ${_ns}::
    COMPONENT ${PROJECT_NAME}-devel
  )
endfunction()
