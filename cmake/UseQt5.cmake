# Qt 5.x ������ cmake���� ����ϱ� ���ϰ� ���ִ� script.
#
# ���� : CMakeLists.txt �� �Ʒ��� ���� �߰�(CMake 2.8.11 ����)
# 
# include(${CMAKE_SOURCE_DIR}/UseQt5.cmake)
# set(Qt5_ROOT "c:/Qt/5.1.0-x86-vc11" CACHE PATH "Qt5 top directory")
# find_qt_5_1(ROOT ${Qt5_ROOT}
#   Widgets
#   Network
#   Sql
#   Xml
#   AxContainer
#   AxBase
#   PrintSupport
#   SerialPort
#   Concurrent
#   Svg
#   Test
#   )
#
# �׷����� �� ������Ʈ�� target_link_libraries() �� Qt::Widgets ���� �־��ָ� �ȴ�.
# (target_link_libraries�� ������ ������!)

include(CMakeParseArguments)

set(_QT_USED_MODULES "" CACHE INTERNAL "Qt5 modules list in use")
set(__redist_dir "${CMAKE_CURRENT_LIST_DIR}/redist" CACHE INTERNAL "Qt5 redist base dir")

set(_QT_5_1_MODULES
  AxBase
  AxContainer
  AxServer
  Concurrent
  Core
  Declarative
  Designer
  Gui
  Help
  LinguistTools
  Multimedia
  MultimediaWidgets
  Network
  OpenGL
  OpenGLExtensions
  PrintSupport
  Qml
  Quick
  QuickTest
  Script
  ScriptTools
  Sensors
  SerialPort
  Sql
  Svg
  Test
  UiTools
  WebKit
  WebKitWidgets
  Widgets
  Xml
  XmlPatterns
  )

# ����:
# 
# find_qt_5_1(ROOT "c:/qt/5.1" Widgets Xml Network)
#
# find_qt_5_1(Widgets Xml)
# 
macro(FIND_QT_5_1)
  set(options) # no option
  set(oneValueArgs ROOT) # no one value args
  set(multiValueArgs) # no multi value args
  cmake_parse_arguments(FQ51 "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  message(STATUS "search Qt5 from ${FQ51_ROOT}")
  set(_modules ${FQ51_UNPARSED_ARGUMENTS})

  # Core/Gui �� ������ �׳� ����.
  set(_QT_USED_MODULES ${_modules};Core;Gui)
  list(REMOVE_DUPLICATES _QT_USED_MODULES)

  # ROOT ������ �ٲٸ� �ٷ� �ٷ� �νĵ� �� �ֵ��� unset�� �ؾ� �ϴ���
  # ��Ⱓ �������� �ֱ� ������ ����ڰ� ROOT�� �������� ���� ��� ��⿡ ����
  # �ƿ� unset�� �ؾ� �ϴ���.
  foreach(_module ${_QT_5_1_MODULES})
	# message("unset(Qt5${_module}_DIR CACHE)")
	unset(Qt5${_module}_DIR CACHE)
  endforeach()

  foreach(_module ${_modules})
	# set(CMAKE_PREFIX_PATH "c:/Qt/5.1.0-x86-vc11/qtbase/lib/cmake/Qt5Widgets")
	set(CMAKE_PREFIX_PATH "${FQ51_ROOT}/qtbase/lib/cmake/Qt5${_module}")
	# message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
	find_package(Qt5${_module})
	# message(STATUS "_Qt5${_module}_OWN_INCLUDE_DIRS = ${_Qt5${_module}_OWN_INCLUDE_DIRS}")
  endforeach()

  # ���(Advanced) ������ ����� cmake-gui�� ǥ�õǴ� �� ����ϰ� ǥ������.
  foreach(_module ${_QT_5_1_MODULES})
	if(Qt5${_module}_FOUND)
	  mark_as_advanced(Qt5${_module}_DIR)
	endif()
  endforeach()
endmacro()

# qt5_wrap_cpp�� pch ������ ���� ����
macro(PCH_QT5_WRAP_CPP outfiles)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs OPTIONS)
  cmake_parse_arguments(_PCH_QT_WRAP_CPP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  
  set(moc_files ${_PCH_QT_WRAP_CPP_UNPARSED_ARGUMENTS})
  set(moc_options ${_PCH_QT_WRAP_CPP_OPTIONS})
  # message(STATUS "outfiles=${outfiles},  moc_files=[${moc_files}],  moc_options=[${moc_options}]")

  # Qt5�� ���ο� option "-b" --> "-f"�ʹ� �޸� ������ ���� ��� ���� #include�� replace���� �ʰ�,
  # ������ �߰��ȴ�. �� ��� 'stdafx.h' �� �ִ´�. 
  qt5_wrap_cpp(${outfiles} ${moc_files} OPTIONS ${moc_options};-bstdafx.h)
endmacro()

# Translations

# get translations directory
# Qt5's cmake support does not seems to provide variable corresponding to
# QT_TRANSLATIONS_DIR in Qt
get_target_property(_qmake Qt5::qmake LOCATION)
execute_process(COMMAND ${_qmake} -query QT_INSTALL_TRANSLATIONS
  OUTPUT_VARIABLE QT_TRANSLATIONS_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

# Call this function with all sources that can have strings to translate
function(qt5_add_tr_sources)
	get_property(translation_sources GLOBAL PROPERTY translation_sources)
	foreach(file ${ARGN})
		list(APPEND translation_sources ${CMAKE_CURRENT_SOURCE_DIR}/${file})
	endforeach(file ${ARGN})
	set_property(GLOBAL PROPERTY translation_sources ${translation_sources})
endfunction()

# Call this to retrieve the list of sources to translate
macro(qt5_get_tr_sources _ts_source_list)
  get_property(translation_sources GLOBAL PROPERTY ${_ts_source_list})
endmacro(qt5_get_tr_sources _ts_source_list)

# The only difference here is that we use MAIN_DEPENDENCY to get the source file in the sources list
macro(wp_qt5_add_translation _qm_files)
  foreach (_current_FILE ${ARGN})
    get_filename_component(_abs_FILE ${_current_FILE} ABSOLUTE)
    get_filename_component(qm ${_abs_FILE} NAME_WE)
    get_source_file_property(output_location ${_abs_FILE} OUTPUT_LOCATION)
    if(output_location)
      file(MAKE_DIRECTORY "${output_location}")
      set(qm "${output_location}/${qm}.qm")
    else(output_location)
      set(qm "${CMAKE_CURRENT_BINARY_DIR}/${qm}.qm")
    endif(output_location)

    add_custom_command(OUTPUT ${qm}
       COMMAND ${Qt5_LRELEASE_EXECUTABLE}
       ARGS ${_abs_FILE} -qm ${qm}
       MAIN_DEPENDENCY ${_abs_FILE}
    )
    set(${_qm_files} ${${_qm_files}} ${qm})
  endforeach (_current_FILE)
endmacro(wp_qt5_add_translation)

# Package Installer
macro(install_qt5_dlls TARGET_DIR)
  if(NOT Qt5Core_FOUND)
	message(FATAL_ERROR "unable to generate install package for Qt!")
  endif()
  
  if(${ARGC} GREATER 1)
	set(__component_name "${ARGV1}")
  else()
	set(__component_name "RunTime")
  endif()
  # message("qt5 install component name is defined ${__component_name}...")

  # Qt5 dll
  foreach(_qt_module ${_qt_5_1_module_to_use})
	if(NOT _qt_module STREQUAL "LinguistTools")
	  get_property(_dll_path
		TARGET Qt5::${_qt_module}
		PROPERTY IMPORTED_LOCATION_RELEASE
		)
	  install(FILES ${_dll_path}
		DESTINATION ${TARGET_DIR}
		COMPONENT ${__component_name}
		)
	endif()
  endforeach()

  # Qt plugins
  foreach(_qt_plugin_name
	  imageformats
	  codecs
	  platforms
	  )
	install(DIRECTORY "${_qt5Core_install_prefix}/plugins/${_qt_plugin_name}"
	  DESTINATION ${TARGET_DIR}
	  COMPONENT ${__component_name}
	  FILES_MATCHING
	  PATTERN "*.dll"
	  # EXCLUDE PATTERN "*d.dll"
	  )
  endforeach()

  # Qt's 3rdparty dependenc'

  # opengl files
  set(_gl_bin_files
	${_qt5Core_install_prefix}/bin/libEGL.dll
	${_qt5Core_install_prefix}/bin/libGLESv2.dll
	)
  
  # icu files
  if(CMAKE_CL_64)
	set(_icu_bin_dir "${__redist_dir}/icu/bin64")
  else()
	set(_icu_bin_dir "${__redist_dir}/icu/bin")
  endif()
  message(STATUS "_icu_bin_dir = ${_icu_bin_dir}")
  set(_icu_bin_files
	"${_icu_bin_dir}/icudt49.dll"
	"${_icu_bin_dir}/icuin49.dll"
	"${_icu_bin_dir}/icuuc49.dll"
	)
  # message("_icu_bin_files = ${_icu_bin_files}")
  # foreach(_icu_bin_file ${_icu_bin_files})
  # 	message("installing ${_icu_bin_file}...")
	install(FILES ${_icu_bin_files};${_gl_bin_files}
	  DESTINATION ${TARGET_DIR}
	  COMPONENT ${__component_name}
	  )
  # endforeach()

  # qt.conf file
  install(FILES ${__redist_dir}/qt/qt.conf
	  DESTINATION ${TARGET_DIR}
	  COMPONENT ${__component_name}
	  )
endmacro()

