# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_fun_numbers_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED fun_numbers_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(fun_numbers_FOUND FALSE)
  elseif(NOT fun_numbers_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(fun_numbers_FOUND FALSE)
  endif()
  return()
endif()
set(_fun_numbers_CONFIG_INCLUDED TRUE)

# output package information
if(NOT fun_numbers_FIND_QUIETLY)
  message(STATUS "Found fun_numbers: 0.0.1 (${fun_numbers_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'fun_numbers' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${fun_numbers_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(fun_numbers_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${fun_numbers_DIR}/${_extra}")
endforeach()
