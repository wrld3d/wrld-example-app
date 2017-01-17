set(headers ${headers} ../src/AboutPage
)
set(currsources
  ../src/AboutPage/AboutPageIndoorPositionTypeMessage.cpp
  ../src/AboutPage/AboutPageIndoorPositionTypeMessage.h
  ../src/AboutPage/AboutPageSenionDataTypeMessage.cpp
  ../src/AboutPage/AboutPageSenionDataTypeMessage.h
  ../src/AboutPage/AboutPageSenionSettingsTypeMessage.cpp
  ../src/AboutPage/AboutPageSenionSettingsTypeMessage.h
  ../src/AboutPage/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AboutPage FILES ${currsources})
include(../src/AboutPage/View/CMakeLists.txt)
