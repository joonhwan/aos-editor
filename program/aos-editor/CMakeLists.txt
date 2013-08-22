set(THIS_PROJ "aos-editor")

include_directories(
  ${XSD_INCLUDE_DIR}
  )

set(${THIS_PROJ}_CPP
  aosl/AosArea.cpp
  aosl/AosCanvas.cpp
  aosl/AosDocument.cpp
  aosl/AosExchangeable.cpp
  aosl/AosLibrary.cpp
  aosl/AosNode.cpp
  aosl/AosResource.cpp
  aosl/AosSequence.cpp
  main.cpp
  )

set(${THIS_PROJ}_H
  aosl/AosArea.h
  aosl/AosCanvas.h
  aosl/AosExchangeContext.h
  aosl/AosExchangeable.h
  aosl/AosLibrary.h
  aosl/AosNode.h
  aosl/AosResource.h
  aosl/AosSequence.h
  )

set(${THIS_PROJ}_MOC_H
  aosl/AosDocument.h
  )

set(${THIS_PROJ}_RC
  )

qt5_wrap_cpp(${THIS_PROJ}_MOC_CPP ${${THIS_PROJ}_MOC_H})

qt5_add_tr_sources(
  ${${THIS_PROJ}_CPP}
  ${${THIS_PROJ}_MOC_H}
  ${${THIS_PROJ}_H}
  ${${THIS_PROJ}_UI}
  )

add_executable(${THIS_PROJ}
  WIN32
  ${${THIS_PROJ}_CPP}
  ${${THIS_PROJ}_H}
  ${${THIS_PROJ}_RC}
  ${${THIS_PROJ}_MOC_CPP}
  )

set_target_properties(${THIS_PROJ}
  PROPERTIES
  FOLDER "program"
  )

target_link_libraries(${THIS_PROJ}
  Qt5::Widgets
  Qt5::Network
  Qt5::Xml
  Qt5::XmlPatterns
  utilcpp
  aoslcpp
  )

