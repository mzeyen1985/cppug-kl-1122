include_guard()

function (monmgr_targetname_component _name _component _output)
  # convert the name into a list
  string (REPLACE
    "::"
    ";"
    _namespace
    "${_name}"
  )

  # extract the targetname
  list (POP_BACK _namespace _targetname)

  # return output based on selected component
  if (_component STREQUAL "NAMESPACE")
    string (REPLACE
      ";"
      "::"
      _namespace
      "${_namespace}"
    )
    set (${_output} "${_namespace}" PARENT_SCOPE)
  elseif (_component STREQUAL "INTERNAL_NAMESPACE")
    string (REPLACE
      ";"
      "-"
      _namespace
      "${_namespace}"
    )
    set (${_output} "${_namespace}" PARENT_SCOPE)
  elseif (_component STREQUAL "NAME")
    set (${_output} "${_targetname}" PARENT_SCOPE)
  else()
    message (FATAL_ERROR
      "Unknown target name component!"
    )
  endif()
endfunction()
