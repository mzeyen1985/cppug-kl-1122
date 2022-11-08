include_guard()

include (monmgr/targetname_component)

function (monmgr_target _type _name)
  monmgr_targetname_component (${_name} NAME _target_name)
  monmgr_targetname_component (${_name} INTERNAL_NAMESPACE _internal_namespace)
  set (_internal_name "${_internal_namespace}-${_target_name}")

  if (_type STREQUAL "get_property")
    list (POP_FRONT ARGN _output)
    get_target_property (
      ${_output}
      "${_internal_name}"
      ${ARGN}
    )
    set (${_output} ${${_output}} PARENT_SCOPE)
  elseif (_type STREQUAL "set_properties")
    set_target_properties (
      "${_internal_name}"
      ${ARGN}
    )
  else()
    cmake_language (CALL
      "target_${_type}" "${_internal_name}"
      ${ARGN}
    )
  endif()
endfunction()
