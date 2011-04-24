# - Find the yaml-cpp include file and library
#
#  YAMLCPP_FOUND - system has yaml-cpp library
#  YAMLCPP_LIBRARY - The libraries needed to use yaml-cpp
#  YAMLCPP_HAVE_H - true if yaml.h is available
#  YAMLCPP_INCLUDE_DIR - yaml.h path
#

if (UNIX)
  find_library(YAMLCPP_LIBRARY NAMES yaml-cpp)
  find_file(YAMLCPP_HAVE_H yaml-cpp/yaml.h )
  find_path(YAMLCPP_H_INCLUDE_DIR yaml-cpp/yaml.h )
  SET(YAMLCPP_INCLUDE_DIR ${YAMLCPP_H_INCLUDE_DIR}/yaml-cpp)
else()
  find_library(
    YAMLCPP_LIBRARY
    NAMES yamlcpp.lib
    NO_DEFAULT_PATH 
    PATHS 
    $ENV{YAMLCPP_ROOT}/lib
  )
  find_file(YAMLCPP_HAVE_H include/yaml.h PATHS $ENV{YAMLCPP_ROOT} NO_DEFAULT_PATH)
  find_path(YAMLCPP_H_INCLUDE_DIR include/yaml.h PATHS $ENV{YAMLCPP_ROOT} NO_DEFAULT_PATH)
  SET(YAMLCPP_INCLUDE_DIR ${YAMLCPP_H_INCLUDE_DIR}/include)
endif(UNIX)

SET(YAMLCPP_FOUND FALSE)
if (YAMLCPP_HAVE_H)
  if (YAMLCPP_LIBRARY)
    SET(YAMLCPP_FOUND TRUE)
  endif (YAMLCPP_LIBRARY)
endif (YAMLCPP_HAVE_H)

if(NOT YAMLCPP_FOUND)
  message(STATUS "YamlCpp Can't be found")
  break()
else()
  message(STATUS "YamlCpp Library: " ${YAMLCPP_LIBRARY} )
  message(STATUS "YamlCpp Header: " ${YAMLCPP_INCLUDE_DIR} )
endif(NOT YAMLCPP_FOUND)

