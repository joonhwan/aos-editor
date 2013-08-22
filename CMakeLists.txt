cmake_minimum_required(VERSION 2.8)

project(aos-editor)

# configuring cmake env
cmake_policy(SET CMP0020 NEW)
SET(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo" CACHE STRING "limited configs" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS "ON")

# packages
include(UseQt5)
set(Qt5_ROOT $ENV{QT5_DIR} CACHE PATH "Qt5 top directory")
find_qt_5_1(ROOT ${Qt5_ROOT}
  Widgets
  Network 
  Sql
  Xml
  XmlPatterns
  PrintSupport
  Concurrent
  Svg
  Test
  )

# compiler options
add_definitions(
  -D_SCL_SECURE_NO_WARNINGS
  )
set(_disabled_warning_option "/wd4819")
set(_extra_compiler_option ${_disabled_warning_option})
foreach(_cmake_cxx_config FLAGS FLAGS_RELEASE FLAGS_DEBUG FLAGS_RELWITHDEBINFO FLAGS_MINSIZEREL)
  string(REPLACE "/EHsc" "/EHa" CMAKE_C_${_cmake_cxx_config}
	"${CMAKE_C_${_cmake_cxx_config}} ${_extra_compiler_option}")
  string(REPLACE "/EHsc" "/EHa" CMAKE_CXX_${_cmake_cxx_config}
	"${CMAKE_CXX_${_cmake_cxx_config}} ${_extra_compiler_option}")
endforeach()

add_subdirectory(library)

foreach(libname utilcpp aoslcpp)
  set_target_properties(${libname}
	PROPERTIES
	FOLDER "library"
	)
endforeach()
include_directories(
  library/aosl-cpp/include
  library/utilcpp/include
  )

add_subdirectory(program)