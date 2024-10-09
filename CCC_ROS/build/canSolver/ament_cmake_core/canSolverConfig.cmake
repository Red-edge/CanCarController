# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_canSolver_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED canSolver_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(canSolver_FOUND FALSE)
  elseif(NOT canSolver_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(canSolver_FOUND FALSE)
  endif()
  return()
endif()
set(_canSolver_CONFIG_INCLUDED TRUE)

# output package information
if(NOT canSolver_FIND_QUIETLY)
  message(STATUS "Found canSolver: 0.0.0 (${canSolver_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'canSolver' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${canSolver_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(canSolver_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${canSolver_DIR}/${_extra}")
endforeach()
